<template>
  <header-nav>商品结算</header-nav>
  <div id="pay">
    <div class="first">
      <p>{{ $store.getters.getPlace.name }} ></p>
      <div class="desc">
        <span></span>您距离当前门店1000米以上，请确认门店是否正确
      </div>
      <div class="contact">联系电话 13883488627 <span>自动填写</span></div>
    </div>
    <div class="second">
      <p>取茶时间: {{waitTime}}</p>
      <div>冰淇淋/鲜食等产品无需等待，可立即向店员领取</div>
    </div>
    <div class="third">
      <div class="third_first" v-for="food in cartList" :key="food">
        <div class="left">
          <div class="imgbox"><img :src="food.info.images[0]" alt="" /></div>
          <div class="name">{{ food.info.name }}</div>
        </div>
        <div class="right">
          <span>¥ {{ food.info.price }}</span>
          <div>x{{ food.count }}</div>
        </div>
      </div>
      <div class="third_second">喜茶券 <span>暂无可用 ></span></div>
      <div class="third_third">备注 <span>不打包 ></span></div>
      <div class="third_fourth">
        共计{{ $store.getters.getSum }}件商品，小计
        <span>¥ {{ $store.getters.getAllPrice }}</span>
      </div>
    </div>
    <div class="fourth">
      <div>选择地址</div>
      <img
        src="/src/assets/imgs/address/edit.png"
        alt=""
        @click="$router.push('/selectaddress')"
      />
    </div>
    <div class="fifth">
      <div>支付方式</div>
      <span>支付宝</span>
    </div>
    <div class="footer">
      <div>
        合计<span>¥ {{ $store.getters.getAllPrice }}</span>
      </div>
      <button @click="pay">支付</button>
    </div>
    <div class="bounced" v-if="error">
      <div>{{ error }}</div>
    </div>
  </div>
</template>

<script>
import HeaderNav from "/src/components/HeaderNav.vue";
import axios from "/src/request/index.js";
export default {
  name: "OrderPay",
  components: {
    HeaderNav,
  },
  data() {
    return {
      cartList: [],
      toList: [],
      error: "",
      addressID: "",
      waitTime: 0,
    };
  },
  beforeMount() {
    this.cartList = this.$store.getters.cartList.filter(
      (item) => item.checked === true
    );
    for (let item of this.cartList) {
      this.toList.push({
        drinkName: item.info.name,
        tipDes: "",
        otherDes: "少糖！！",
        drinkNum: item.count,
      });
    }
    axios
      .get("/address/list")
      .then((res) => {
        if (res.data.data[this.$store.getters.getAddrNum].id) {
          this.addressID = res.data.data[this.$store.getters.getAddrNum].id;
        } else {
          this.bounceError("请填写地址");
        }
        // console.log(res.data);
      })
      .catch((err) => {
        console.log(err);
      });
    axios
      .post(`order/wait_time?store=${this.$store.getters.getPlace.id}`)
      .then((res) => {
        this.waitTime = res.data.data.waitTime;
        // console.log(res);
      })
      .catch((err) => {
        console.log(err);
      })
  },
  methods: {
    bounceError(msg) {
      this.error = msg;
      setTimeout(() => {
        this.error = "";
      }, 2000);
    },
    pay() {
      if (this.$store.getters.getSum) {
        axios
          .put(`/order/pay?cost=${this.$store.getters.getAllPrice}`)
          .then((res) => {
            this.bounceError(res.data.message);
            if (res.data.code === -1) {
              setTimeout(() => {
                this.$router.push("/recharge");
              }, 1000);
            } else if (res.data.code === 200) {
              this.$store.getters.cartList.length = 0;
              let order = {
                store: this.$store.getters.getPlace.id,
                delId: this.addressID,
                isTakeOut: true,
                products: this.toList,
              };
              axios
                .post("/order/add", order)
                .then((res) => {
                  this.$store.getters.cartList.length = 0;
                  setTimeout(() => {
                    this.$router.push("/order");
                  }, 1000);
                })
                .catch((err) => {
                  console.log(err);
                });
            }
          })
          .catch((err) => {
            console.log(err);
          });
      } else {
        this.bounceError("您还未选择商品");
      }
    },
  },
};
</script>

<style scoped>
#pay {
  width: 100%;
  min-height: 85%;
  padding: 44px 0 50px;
  background-color: #fff;
}
#pay .first {
  background-color: #fafafa;
  padding: 5px 3%;
  height: 122px;
  width: 94%;
}
#pay .first > p {
  font-size: 18px;
  font-weight: 600;
  color: #323232;
}
#pay .first .desc {
  margin: 10px 0 30px;
  font-size: 12px;
  color: #aaaaaa;
}
#pay .first .desc > span {
  width: 10px;
  height: 10px;
  display: inline-block;
  background-color: red;
  margin-right: 5px;
}
#pay .first .contact {
  margin-left: 8px;
  font-size: 15px;
  color: #666666;
}
#pay .first .contact > span {
  color: rgb(240, 171, 116);
  font-size: 12px;
  float: right;
  margin: 1px;
}
#pay .second {
  background-color: #fafafa;
  margin-top: 10px;
  padding: 5px 5%;
  height: 68px;
  width: 90%;
}
#pay .second > p {
  font-size: 15px;
  color: #666666;
  padding: 5px 0 10px;
}
#pay .second > div {
  color: rgb(240, 171, 116);
  font-size: 12px;
}
#pay .third {
  background-color: #fafafa;
  margin-top: 10px;
  padding: 5px 5%;
  width: 90%;
}
#pay .third .third_first {
  width: 100%;
  height: 100px;
  padding-bottom: 10px;
}
#pay .third .third_first .left {
  float: left;
  position: relative;
}
#pay .third .third_first .left .imgbox {
  width: 80px;
  height: 80px;
  margin-right: 10px;
  overflow: hidden;
}
#pay .third .third_first .left .imgbox > img {
  margin-left: -20px;
  width: 120px;
  height: 80px;
}
#pay .third .third_first .left .name {
  position: absolute;
  top: 10px;
  left: 90px;
  min-width: 100px;
  color: #333333;
  display: inline-block;
}
#pay .third .third_first .right {
  float: right;
  margin-top: 10px;
}
#pay .third .third_first .right > div {
  color: #aaaaaa;
  width: 18px;
  font-size: 14px;
  margin-top: 5px;
  margin-left: 14px;
}
#pay .third .third_second {
  font-size: 15px;
  color: #666666;
  width: 100%;
  height: 60px;
  line-height: 60px;
}
#pay .third .third_second > span {
  color: #aaaaaa;
  float: right;
}
#pay .third .third_third {
  font-size: 15px;
  color: #666666;
  width: 100%;
  height: 60px;
  line-height: 60px;
}
#pay .third .third_third > span {
  color: #aaaaaa;
  float: right;
}
#pay .third .third_fourth {
  text-align: right;
  font-size: 15px;
  color: #aaaaaa;
  line-height: 60px;
}
#pay .third .third_fourth > span {
  font-size: 18px;
  color: black;
}
#pay .fourth {
  background-color: #fafafa;
  margin-top: 10px;
  padding: 5px 5%;
  height: 50px;
  width: 90%;
}
#pay .fourth > div {
  font-size: 15px;
  line-height: 50px;
  color: #666666;
  display: inline-block;
}
#pay .fourth > img {
  width: 24px;
  height: 24px;
  float: right;
  margin: 20px 10px;
}
#pay .fifth {
  background-color: #fafafa;
  margin-top: 10px;
  padding: 5px 5%;
  height: 50px;
  width: 90%;
}
#pay .fifth > div {
  font-size: 15px;
  line-height: 50px;
  color: #666666;
  display: inline-block;
}
#pay .fifth > span {
  font-size: 12px;
  line-height: 50px;
  color: #666666;
  float: right;
}
#pay .footer {
  margin-top: 10px;
  text-align: center;
}
#pay .footer > div {
  line-height: 40px;
  font-size: 15px;
  color: #666666;
  display: inline-block;
}
#pay .footer > div > span {
  margin-left: 5px;
  color: #333;
}
#pay .footer > button {
  font-size: 15px;
  color: white;
  background-color: orange;
  border: none;
  float: right;
  margin-right: 15px;
  padding: 10px;
}
#pay .bounced {
  position: fixed;
  width: 150px;
  height: 35px;
  background-color: rgba(0, 0, 0, 0.7);
  z-index: 9999;
  margin: 0 auto;
  bottom: 200px;
  left: 125px;
  border-radius: 10px;
}
#pay .bounced div {
  line-height: 35px;
  color: white;
  text-align: center;
  font-size: 12px;
}
</style>