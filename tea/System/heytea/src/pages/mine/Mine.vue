<template>
  <div id="mine">
    <div class="header"></div>
    <div :class="nav_header" v-if="nav_show">我的</div>
    <div class="focus">
      <img src="/src/assets/imgs/mine/mine_focus.png" alt="">
    </div>
    <div class="info">
      <div class="left">
        <div class="hey">
          <div v-if="logged" class="logged">
            <p>Hey,{{user.username}}</p>
            <div>嘭，来杯灵感</div>
          </div>
          <div v-else class="unlogged"></div>
        </div>
        <div class="member">
          <p><span>GO</span>会员</p>
          <div v-if="logged" class="logged">Lv1</div>
          <div v-else class="unlogged">
            <button @click="handleClick()">点击登录</button>
            <login ref="login" />
          </div>
        </div>
      </div>
      <div class="right">
        <img :src="user.avatar" alt="" v-if="logged">
        <img src="/src/assets/imgs/mine/mine_photo_unlogged.png" alt="" v-else>
      </div>
      <div class="bottom">
        <div class="item">
          <img src="/src/assets/imgs/mine/mine_points.png" alt="">
          <span v-if="logged">0</span>
          <span v-else>***</span>
          <div>积分商城</div>
        </div>
        <div class="item">
          <img src="/src/assets/imgs/mine/mine_tickets.png" alt="">
          <span v-if="logged">0</span>
          <span v-else>***</span>
          <div>喜茶券</div>
        </div>
        <div class="item">
          <img src="/src/assets/imgs/mine/mine_wallet.png" alt="">
          <span v-if="logged">0</span>
          <span v-else>***</span>
          <div>钱包</div>
        </div>
        <div class="item">
          <img src="/src/assets/imgs/mine/mine_gift.png" alt="">
          <span v-if="logged">0</span>
          <span v-else>***</span>
          <div>阿喜有礼</div>
        </div>
      </div>
    </div>
    <div class="news">
      <p class="title">星球播报</p>
      <div class="slider">
        <img src="/src/assets/imgs/mine/mine_slider.png" alt="">
      </div>
      <div class="task">
        <div class="left">
          <p>任务中心</p>
          <div>MISSION CENTER</div>
        </div>
        <div class="right">
          <img src="/src/assets/imgs/mine/mine_mission.png" alt="">
        </div>
      </div>
    </div>
    <div class="more">
      <div class="item" v-for="item in items" :key="item.choice">
        <p class="left">{{item.choice}}</p>
        <div class="right">{{item.desc}}<span>❯</span></div>
      </div>
    </div>
    <button v-if="logged" class="logout" @click="logout()">退 出 登 录</button>
    <div class="bounced" v-if="error">
      <div>{{ error }}</div>
    </div>
  </div>
</template>

<script>
import Login from './login/Login.vue';
import axios from "/src/request/index.js";
export default {
  name: 'Mine',
  components: {
    Login
  },
  beforeMount() {
    if (this.$store.state.isLogin) {
      axios.get('/user/info')
      .then((res) => {
          this.user = res.data.data;
      })
      .catch((err) => {
          console.log(err);
      })
    }
  },
  beforeUpdate() {
    if (this.$store.state.isLogin) {
      axios.get('/user/info')
      .then((res) => {
          this.user = res.data.data;
      })
      .catch((err) => {
          console.log(err);
      })
    }
  },
  data() {
    return {
      error: "",
      nav_show: false,
      nav_header: "nav_header",
      user: {},
      items: [
        {choice: "会员码", desc: "门店扫码积分、喜茶钱包和阿喜有礼支付"},
        {choice: "兑换中心", desc: "兑换星球会员、喜茶券和阿喜有礼"},
        {choice: "主题封面", desc: ""},
        {choice: "发票助手", desc: ""},
        {choice: "联系客服", desc: ""},
        {choice: "消息中心", desc: ""},
        {choice: "更多", desc: ""}
      ],
    }
  },
  methods: {
    bounceError(msg) {
          this.error = msg;
          setTimeout(() => {
              this.error = "";
          }, 2000);
    },
    handleClick() {
      this.$refs.login.open();
    },
    logout() {
      this.$store.dispatch('logout');
      this.bounceError('退出成功');
    }
  },
  computed: {
    logged() {
      return this.$store.state.isLogin;
    },
  },
}
</script>

<style scoped>
#mine {
  width: 100%;
  background-color: whitesmoke;
}
#mine .header {
  width: 100%;
  height: 50px;
  position: fixed;
  top: 0;
  z-index: 1;
  background-color: white;
}
#mine .nav_header {
  width: 100%;
  height: 50px;
  line-height: 50px;
  font-size: 18px;
  font-weight: 600;
  color: #3A3A3A;
  text-align: center;
  position: fixed;
  top: 50px;
  z-index: 1;
  background-color: white;
}
#mine .nav_header_transition {
  width: 100%;
  height: 50px;
  line-height: 50px;
  font-size: 18px;
  font-weight: 600;
  color: #3A3A3A;
  text-align: center;
  position: fixed;
  top: 50px;
  z-index: 1;
  background-color: white;
  opacity: 0.8;
}
#mine .focus {
  width: 100%;
  height: 370px;
  padding-bottom: 50px;
  background-color: white;
}
#mine .focus img {
  width: 100%;
  height: 340px;
}
#mine .info {
  width: 90%;
  height: 245px;
  margin: -60px 5% 20px 5%;
  background-color: white;
  border-radius: 7px;
}
#mine .info .left {
  float: left;
}
#mine .info .left .hey {
  margin-left: 10px;
}
#mine .info .left .hey .logged p {
  margin: 2px 0;
  color: rgb(129, 46, 21);
  font-family:'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
  font-weight: 600;
}
#mine .info .left .hey .logged div {
  font-size: 13px;
  color: rgb(129, 46, 21);
  font-weight: 500;
}
#mine .info .left .hey .unlogged {
  height: 46px;
}
#mine .info .left .member {
  padding: 10px 20px;
}
#mine .info .left .member p {
  font-size: 20px;
  font-weight: 700;
  color: #404040;
  margin: 3px 0;
}

#mine .info .left .member p span {
  font-size: 22px;
  font-weight: 600;
}
#mine .info .left .member .logged {
  width: 35px;
  font-size: 12px;
  font-weight: 700;
  color: #606060;
  border: 1px solid #606060;
  border-radius: 5px;
  margin-top: 6px;
  text-align: center;
}
#mine .info .left .member .unlogged button {
  width: 70px;
  height: 23px;
  font-size: 10px;
  background-color: #333;
  color: white;
  border-radius: 6px;
}
#mine .info .right {
  float: right;
  margin-top: 25px;
  margin-right: 30px;
}
#mine .info .right img {
  width: 80px;
  height: 80px;
  border-radius: 50%;
}
#mine .info .bottom {
  clear: both;
  width: 90%;
  height: 120px;
  margin: 20px 5%;
  border-top: 1px solid #F5F6F9;
  display: flex;
  justify-items: center;
  text-align: center;
}
#mine .info .bottom .item {
  flex: 1;
}
#mine .info .bottom .item img {
  width: 54px;
  height: 54px;
}
#mine .info .bottom .item span {
  display: block;
  font-size: 20px;
  color: #575757;
}
#mine .info .bottom .item div {
  font-size: 13px;
  margin-top: 5px;
  color: #575757;
}
#mine .news {
  width: 90%;
  margin: 20px 5%;
}
#mine .news .title {
  margin: 0 0 12px 3px;
  color: #444444;
}
#mine .news .slider img {
  width: 320px;
  height: 115px;
}
#mine .news .task {
  width: 100%;
  height: 145px;
  background-color: white;
  border-radius: 8px;
  margin-top: 15px;
  display: flex;
  align-items: center;
}
#mine .news .task .left {
  flex: 1;
  text-align: center;
}
#mine .news .task .left p {
  margin: 6px 0;
  font-weight: 500;
  color: #3A3A3A;
}
#mine .news .task .left div {
  font-size: 10px;
  font-weight: 500;
  color: #3A3A3A;
}
#mine .news .task .right {
  flex: 1;
  text-align: center;
}
#mine .news .task .right img {
  width: 125px;
  height: 125px;
}
#mine .more {
  width: 100%;
  padding-bottom: 30px;
  margin-bottom: 20px;
  border-bottom: 1px solid #e0dddd;
}
#mine .more .item {
  clear: both;
  width: 100%;
  height: 70px;
  line-height: 70px;
  background-color: white;
}
#mine .more .item .left {
  float: left;
  margin-left: 20px;
  color: #4C4C4C;
  font-size: 16px;
  font-weight: 500;
}
#mine .more .item .right {
  float: right;
  font-size: 14px;
  margin-right: 20px;
  color: #CFD0D2;
}
#mine .more .item .right span {
  padding-left: 12px;
}
#mine .logout {
  color: #333;
  font-size: 18px;
  width: 90%;
  height: 40px;
  background-color: rgb(247, 165, 14);
  border-radius: 20px;
  margin: 0 5% 50px;
  border: none;
}
#mine .bounced {
  position: relative;
  width: 150px;
  height: 35px;
  background-color: rgba(0, 0, 0, 0.7);
  z-index: 9999;
  margin: 0 auto;
  border-radius: 10px;
}
#mine .bounced div {
  line-height: 35px;
  color: white;
  text-align: center;
  font-size: 12px;
}
</style>