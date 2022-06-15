<template>
  <header-nav>订单详情</header-nav>
  <div id="order_detail">
    <div class="first">
      <p>订单已完成</p>
      <div>感谢您对喜茶的支持，欢迎再次光临</div>
    </div>

    <div class="second">
      <div class="second_first">
        <div class="left">
          <p>{{order.store}}</p>
          <div>交子大道300号"悠方购物中心"一层132/133/136/137号</div>
        </div>
        <img
          src="/src/assets/imgs/orderDetail/orderDetail_contact.png"
          class="right"
        />
      </div>
      <div class="second_second" v-for="(item, index) in order.drink" :key="index">
        <div class="left">
          <div class="imgbox"><img :src="item.images[0]" alt="" /></div>
          <div class="desc">{{item.name}}</div>
        </div>
        <div class="right">
          <span>¥ {{item.price}}</span>
          <div>x{{item.num}}</div>
        </div>
      </div>
      <div class="second_third">
        <div class="left">商品总价(含小料)</div>
        <div class="right">¥ {{order.price}}</div>
      </div>
      <div class="second_fourth">
        <div>共{{order.drinkNum}}件商品，合计<span>¥ {{order.price}}</span></div>
      </div>
    </div>
    <div class="third">
      <p>订单信息</p>
      <div>下单时间: <span>{{order.createTime}}</span></div>
      <div>取茶号: <span>{{order.code}}</span></div>
      <div>
        订单编号:
        <span>{{order.id}}</span>
        <button>复制</button>
      </div>
      <div>备注信息: <span>{{order.otherDes}}</span></div>
    </div>

    <div class="footer">如需退款，请致电门店</div>
  </div>
</template>

<script>
import HeaderNav from '/src/components/HeaderNav.vue';
import axios from '/src/request/index.js';
export default {
  name: "OrderDetail",
  components: {
    HeaderNav,
  },
  data() {
    return {
      order: {},
    }
  },
  beforeMount() {
    axios.get('/order/list')
    .then((res) => {
      // console.log(res);
      this.order = res.data.data[this.$store.getters.getOrderNum];
      // console.log(this.order);
    })
    .catch((err) => {
      console.log(err);
    })
  },
};
</script>

<style scoped>
#order_detail {
  width: 90%;
  min-height: 95%;
  padding: 64px 5% 0;
  text-align: center;
  background-color: rgb(242, 242, 242);
}
#order_detail .first {
  background-color: white;
  padding: 5px 5%;
  height: 70px;
  width: 90%;
  line-height: 35px;
}
#order_detail .first p {
  font-size: 15px;
  font-style: normal;
  text-align: center;
  color: #333333;
}
#order_detail .first div {
  font-size: 11px;
  font-style: normal;
  font-weight: lighter;
  text-align: center;
  line-height: 15px;
  color: #aaaaaa;
}
#order_detail .second {
  background-color: white;
  margin-top: 20px;
  padding: 5px 5%;
  /* height: 264px; */
  width: 90%;
}
#order_detail .second .second_first {
  width: 100%;
  height: 80px;
  border-bottom: 1px solid rgba(0, 0, 0, 0.1);
}
#order_detail .second .second_first .left {
  width: 60%;
  float: left;
  text-align: left;
}
#order_detail .second .second_first .left > p {
  color: #333333;
  line-height: 35px;
}
#order_detail .second .second_first .left > div {
  color: #aaaaaa;
  font-size: 12px;
}
#order_detail .second .second_first .right {
  margin-top: 10px;
  float: right;
  width: 113px;
  height: 64px;
}
#order_detail .second .second_second {
  width: 100%;
  height: 100px;
  padding-bottom: 10px;
  border-bottom: 1px solid rgba(0, 0, 0, 0.1);
}
#order_detail .second .second_second .left {
  float: left;
  position: relative;
}
#order_detail .second .second_second .left .imgbox {
  width: 100px;
  height: 100px;
  margin-right: 10px;
  display: inline-block;
  overflow: hidden;
}
#order_detail .second .second_second .left .imgbox > img {
  width: 160px;
  height: 100px;
  margin: 0 -30px;
}
#order_detail .second .second_second .left .desc {
  position: absolute;
  top: 10px;
  left: 110px;
  min-width: 100px;
  color: #333333;
  display: inline-block;
}
#order_detail .second .second_second .right {
  float: right;
  margin-top: 10px;
}
#order_detail .second .second_second .right > div {
  color: #aaaaaa;
  width: 18px;
  font-size: 14px;
  margin-top: 5px;
  margin-left: 14px;
}
#order_detail .second .second_third {
  padding: 8px 0;
  width: 100%;
  height: 18px;
  border-bottom: 1px solid rgba(0, 0, 0, 0.1);
}
#order_detail .second .second_third .left {
  float: left;
  font-size: 14px;
  color: #aaaaaa;
  margin-left: 5px;
}
#order_detail .second .second_third .right {
  float: right;
  font-size: 14px;
  margin-right: 5px;
}
#order_detail .second .second_fourth {
  width: 100%;
  padding: 10px 0;
  text-align: right;
}
#order_detail .second .second_fourth > div {
  font-size: 14px;
  color: #aaaaaa;
}
#order_detail .second .second_fourth > div > span {
  margin-left: 5px;
  color: black;
}
#order_detail .third {
  background-color: white;
  margin-top: 20px;
  padding: 5px 5%;
  height: 150px;
  width: 90%;
}
#order_detail .third > p {
  text-align: left;
  font-size: 15px;
  padding: 10px 0;
  color: #666666;
  border-bottom: 1px solid rgba(0, 0, 0, 0.1);
}
#order_detail .third > div {
  text-align: left;
  font-size: 12px;
  color: #aaaaaa;
  line-height: 25px;
}
#order_detail .third > div > span {
  color: #333333;
  font-weight: 600;
}
#order_detail .third > div > button {
  float: right;
  border: none;
  background-color: inherit;
  color: rgb(158, 17, 17);
  margin-top: 2px;
}
#order_detail .footer {
  margin-top: 50px;
  font-size: 8px;
  color: #aaaaaa;
}
</style>