<template>
  <header-nav>会员储值</header-nav>
  <div id="recharge">
    <div class="first">
      <div class="left">
        <p>账户余额（元）</p>
        <span>{{ balance }}</span>
        <div>交易记录</div>
      </div>
      <img class="right" src="/src/assets/imgs/recharge/recharge_bag.png" />
    </div>
    <div class="second">
      <p>储值金额</p>
      <div class="items">
        <div v-for="(item, index) of rechargeList" :key="item" class="item" :class="[{isActive: selectNum === index}, {notActive: selectNum !== index}]" @click="selectItem(index)">
          {{ item }}<span>元</span>
        </div>
      </div>
    </div>
    <div class="third">
      <p>使用说明</p>
      <div>
        1. 储值成功后，不可退款，请根据自己的消费情况充值。<br />
        2. 储值余额不可提现，不可转移、转赠。<br />
        3.
        储值金额按国家法律、法规开具符合规定的发票，后续凭储值余额消费时，不再开具发票。如需发票请至喜茶点单小程序个人中心联系客服。<br />
        4.
        储值不累计会员成长值、积分与宝石，订单消费时以实际订单支付金额累计会员成长值、积分与宝石。<br />
        5.
        储值余额可在喜茶内地线下门店、喜茶全国门店、喜茶点单小程序在线支付使用。<br />
      </div>
    </div>
    <div class="footer">
      <input type="checkbox" v-model="agree" />
      <div>我已阅读并同意《储值协议》</div>
      <button @click="recharge">充值</button>
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
  name: "Recharge",
  components: {
    HeaderNav,
  },
  beforeMount() {
    axios.get('/user/info')
    .then((res) => {
        this.balance = res.data.data.balance;
    })
    .catch((err) => {
        console.log(err);
    })
  },
  beforeUpdate() {
    axios.get('/user/info')
    .then((res) => {
        this.balance = res.data.data.balance;
    })
    .catch((err) => {
        console.log(err);
    })
  },
  data() {
    return {
      error: '',
      rechargeList: [100, 200, 300, 400, 600, 800],
      selectNum: -1,
      rechargeNum: 0,
      agree: false,
      balance: 0,
    };
  },
  methods: {
    bounceError(msg) {
      this.error = msg;
      setTimeout(() => {
          this.error = "";
      }, 2000);
    },
    selectItem(index) {
      this.selectNum = index;
      this.rechargeNum = this.rechargeList[index];
    },
    recharge() {
      if (this.agree && this.rechargeNum) {
        axios.put(`/user/recharge?amount=${this.rechargeNum}`)
        .then((res) => {
          this.bounceError(res.data.message);
          setTimeout(() => {
            this.$router.back();
          }, 1000);
        })
        .catch((err) => {
          console.log(err);
        })
      } else if (!this.agree) {
        this.bounceError("请勾选同意协议");
      } else {
        this.bounceError("请选择充值金额");
      }
    }
  },
};
</script>

<style scoped>
#recharge {
  position: absolute;
  top: 44px;
  bottom: 0;
  left: 0;
  right: 0;
}
#recharge .first {
  width: 90%;
  height: 110px;
  padding: 27px 5%;
}
#recharge .first .left {
  float: left;
}
#recharge .first .right {
  float: right;
  width: 186px;
  height: 106px;
}
#recharge .first .left > p {
  color: #5a5b5c;
  padding: 5px 0;
  font-size: 13px;
}
#recharge .first .left > span {
  display: block;
  padding: 5px 0;
  font-size: 21px;
  font-weight: 700;
  color: #5a5b5c;
}
#recharge .first .left > div {
  color: #adb838;
  padding: 5px 0;
  font-size: 13px;
}
#recharge .second {
  clear: both;
  width: 90%;
  height: 193px;
  padding: 0 5%;
  margin-bottom: 20px;
}
#recharge .second > p {
  font-size: 16px;
  color: #5a5b5c;
  font-weight: 700;
  margin-bottom: 10px;
}
#recharge .second .items {
  width: 100%;
  height: 162px;
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  justify-items: center;
  align-content: space-between;
  justify-content: space-around;
}
#recharge .second .items .item {
  flex: 0;
  padding: 25px 0;
  flex-basis: 30%;
  font-size: 20px;
  font-weight: 700;
  text-align: center;
  border-radius: 4px;
}
#recharge .second .items .item > span {
  font-size: 13px;
  font-weight: 300;
}
#recharge .third {
  width: 90%;
  height: 175px;
  padding: 0 5%;
}
#recharge .third > p {
  font-size: 16px;
  color: #5a5b5c;
  font-weight: 700;
  margin-bottom: 10px;
}
#recharge .third > div {
  font-size: 12px;
  color: #919293;
}
#recharge .footer {
  position: fixed;
  left: 0;
  bottom: 0;
  width: 90%;
  padding: 0 5%;
  box-shadow: 0 0 10px rgb(6 6 1 / 10%);
  background-color: #ffffff;
}
#recharge .footer > div {
  display: inline-block;
  margin-left: 5px;
  margin-right: 12px;
  font-size: 12px;
  color: #606266;
  padding: 18px 0;
}
#recharge .footer > button {
  width: 100%;
  height: 35px;
  background-color: #666666;
  color: #ffffff;
  margin-bottom: 15px;
  border-radius: 50px;
  border: none;
}
.isActive {
  background-color: rgba(0, 0, 0, 0.2);
  color: white;
}
.notActive {
  color: #5a5b5c;
  background-color: #f1f8fa;
}
#recharge .bounced {
  position: relative;
  width: 150px;
  height: 35px;
  background-color: rgba(0, 0, 0, 0.7);
  z-index: 9999;
  margin: 0 auto;
  border-radius: 10px;
}
#recharge .bounced div {
  line-height: 35px;
  color: white;
  text-align: center;
  font-size: 12px;
}
</style>