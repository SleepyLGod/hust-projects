<template>
  <div class="order">
    <div class="order-header">
      <div
        class="nowOrder"
        :class="order_active === 0 ? 'order-active' : ''"
        @click="changeTab(0)"
      >
        当前订单
      </div>
      <div
        class="historyOrder"
        :class="order_active === 1 ? 'order-active' : ''"
        @click="changeTab(1)"
      >
        历史订单
      </div>
    </div>
    <div class="unlogged" v-show="!$store.state.isLogin" @click="$router.push('/mine')"><div>请先登录</div></div>
    <div class="logged" v-show="$store.state.isLogin">
      <div v-if="order_active === 0" class="order-content">
        <orderItem v-for="(item, index) in showList" :key="index" :food='item'  @click="toDetail(index)"></orderItem>
      </div>
      <div v-if="order_active === 1" class="history-content">
        <orderItem v-for="(item, index) in showList" :key="index" :food='item'  @click="toDetail(index)"></orderItem>
      </div>
    </div>
    <div class="footer">没有更多了</div>
  </div>
</template>

<script>
import orderItem from "./childCom/orderItem.vue";
import axios from '/src/request/index.js';
export default {
  name: "Order",
  components: {
    orderItem,
  },
  data() {
    return {
      order_active: 0,
      showList: [],
    };
  },
  beforeMount() {
    if (this.$store.state.isLogin) {
      axios.get('/order/list')
      .then((res) => {
        // console.log(res);
        this.showList = res.data.data;
      })
      .catch((err) => {
        console.log(err);
      })
    }
  },
  methods: {
    changeTab(index) {
      this.order_active = index;
    },
    toDetail(index) {
      this.$store.commit('SELECTORDERNUM', index);
      this.$router.push('/orderdetail');
    }
  },
};
</script>

<style scoped>
.order {
  background-color: rgb(245, 245, 245);
  min-height: 100%;
}
.order-header {
  display: flex;
  position: fixed;
  top: 0;
  width: 100%;
  height: 80px;
  background-color: #fff;
}
.order-header div {
  flex: 1;
  display: flex;
  justify-content: center;
  align-items: center;
}
.order-active {
  color: orange;
  border-bottom: 5px solid orange;
}
.order-content {
  padding-top: 100px;
}
.history-content {
  padding-top: 100px;
}
.unlogged {
  position: absolute;
  top: 50%;
  width: 60%;
  margin: 0 20%;
  text-align: center;
}
.unlogged > div {
  font-size: 20px;
  padding:15px;
  color: white;
  border-radius: 10px;
  background-color: orange;
}
.footer {
  text-align: center;
  margin-top: 30px;
  padding-bottom: 80px;
  color: rgb(180, 173, 173);
  font-size: 16px;
}
</style>