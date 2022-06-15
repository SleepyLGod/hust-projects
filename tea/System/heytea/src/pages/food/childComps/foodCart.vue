<template>
  <div class="cart" v-if="$store.getters.cartList.length">
    <img
      :class="{ activeImg: 'isActive' }"
      src="/src/assets/imgs/food/cart.png"
      alt=""
      @click="cartImgClick"
    />
    <p>￥{{ allPrice }}</p>
    <div class="right" @click="pay">结算</div>
    <div class="cartlists" v-show="isShow">
      <div class="top">
        <div class="t-left">
          <span
            class="checkbox"
            :class="{ checkboxActive: isAll }"
            @click="isAllSelect"
          ></span
          ><span>全选</span>
        </div>
        <div class="t-right" @click="clearAll">清理购物车</div>
      </div>
      <div class="foods" v-for="(item, i) in payList" :key="i">
        <span
          class="inp"
          :class="{ inpActive: item.checked }"
          @click="
            {
              item.checked = !item.checked;
            }
          "
        ></span>
        <div class="imgbox"><img :src="item.info.images[0]" alt="" /></div>
        <div class="text">
          <div>{{ item.info.name }}</div>
          <div class="ntwo">￥{{ item.info.price }}</div>
        </div>
        <div class="foods-right">
          <span class="sub" @click="subFood(i)">-</span>
          <span>{{ item.count }}</span>
          <span class="add" @click="addFood(i)">+</span>
        </div>
      </div>
    </div>
    <div class="bounced" v-if="error">
      <div>{{ error }}</div>
    </div>
  </div>
</template>

<script>
export default {
  name: "foodCart",
  props: {
    food: Object
  },
  data() {
    return {
      isShow: false,
      isAll: true,
      error: '',
    };
  },
  methods: {
    bounceError(msg) {
      this.error = msg;
      setTimeout(() => {
          this.error = "";
      }, 2000);
    },
    cartImgClick() {
      this.isShow = !this.isShow;
      this.$emit("changeBgc");
    },
    addFood(i) {
      this.$store.getters.cartList[i].count++;
    },
    subFood(i) {
      if(this.$store.getters.cartList[i].count > 1){
        this.$store.getters.cartList[i].count--;
      } else if (this.$store.getters.cartList[i].count === 1) {
        this.$store.getters.cartList.splice(i, 1);
      }
    },
    isAllChange() {
      this.isAll = !this.isAll;
    },
    isAllSelect() {
      this.isAll = !this.isAll;
      let isAll = this.$store.getters.cartList.find((item) => !item.checked);
      if (isAll) {
        this.$store.getters.cartList.forEach((item) => {
          item.checked = true;
        });
      } else {
        this.$store.getters.cartList.forEach((item) => {
          item.checked = false;
        });
      }
    },
    clearAll() {
      this.$store.getters.cartList.length = 0;
    },
    pay() {
      if (this.allPrice) {
        this.$router.push('/orderpay');
      }
      else {
        this.bounceError('请选择要结算的物品');
      }
    }
  },
  computed: {
    payList() {
      return this.$store.getters.cartList;
    },
    payCount() {
      return this.$store.getters.getLength;
    },
    allPrice() {
      let pri = 0;
      for (let item of this.$store.getters.cartList) {
        pri = pri + item.checked * item.count * item.info.price;
      }
      return pri;
    },
  },
};
</script>


<style scoped>
.cart {
  position: fixed;
  bottom: 50px;
  left: 0;
  width: 100%;
  height: 50px;
  z-index: 1;
  background-color: rgb(214, 205, 205);
}
.cart>p {
  margin: 0;
}
.cart > img {
  position: absolute;
  width: 40px;
  left: 15px;
  border-radius: 100%;
  box-shadow: 3px 3px 3px #888888;
}
.checkbox {
  display: inline-block;
  width: 10px;
  height: 10px;
  border: 1px solid #000;
  border-radius: 100%;
}
.checkboxActive {
  background-color: rgb(226, 128, 36);
}
.inp {
  display: inline-block;
  width: 10px;
  height: 10px;
  border: 1px solid #000;
  border-radius: 100%;
}
.inpActive {
  background-color: rgb(226, 128, 36);
}
.inp {
  float: left;
  margin: 20px 10px 0px 10px;
}
.cart p {
  position: absolute;
  left: 70px;
  display: inline-block;
  line-height: 50px;
  /* line-height: 100px; */
  color: #000;
}
.right {
  float: right;
  width: 80px;
  height: 50px;
  line-height: 50px;
  background-color: rgb(226, 128, 36);
  text-align: center;
  color: #fff;
}
.cartlists {
  width: 94%;
  background-color: #fff;
  position: fixed;
  bottom: 100px;
  left: 0;
  padding: 10px 3%;
  max-height: 300px;
  overflow: scroll;
}
.cartlists .top {
  height: 30px;
}
.cartlists .top .t-left {
  float: left;
}
.cartlists .top .t-left span {
  margin-left: 10px;
  font-size: 15px;
}
.cartlists .top .t-right {
  float: right;
  font-size: 10px;
  color: rgb(136, 133, 133);
}
.foods {
  width: 100%;
  height: 80px;
  padding: 15px 0px 15px 0px;
  font-size: 15px;
  color: #000;
}
.foods .imgbox {
  width: 60px;
  height: 60px;
  float: left;
  overflow: hidden;
}
.foods .imgbox > img {
  width: 120px;
  height: 60px;
  margin-left: -30px;
}
.foods .text {
  float: left;
  margin-left: 20px;
}
.text div {
  margin-top: 5px;
}
.text .ntwo {
  margin-top: 15px;
}
.foods-right {
  float: right;
}
.foods-right span {
  margin: 30px 5px 0px 5px;
}
.foods-right .add,
.sub {
  display: inline-block;
  width: 15px;
  height: 15px;
  line-height: 15px;
  border-radius: 100%;
  text-align: center;
}
.foods-right .sub {
  background-color: rgb(136, 133, 133);
}
.foods-right .add {
  background-color: rgb(226, 128, 36);
}
.bounced {
  position: relative;
  width: 150px;
  height: 35px;
  background-color: rgba(0, 0, 0, 0.7);
  z-index: 9999;
  margin: 0 auto;
  border-radius: 10px;
}
.bounced div {
  line-height: 35px;
  color: white;
  text-align: center;
  font-size: 12px;
}
</style>