<template>
  <header-nav>注册</header-nav>
  <div class="register">
    <div class="logo">
      <img src="./../../assets/imgs/register/logo.jpg" alt="my register img" />
    </div>
    <!-- 输入框 -->
    <div class="input-group">
      <input type="text" v-model="inputphone" placeholder="请输入手机号" />
      <span @click="emptyinputphone($event)" v-if="inputphone"
        ><img src="./../../assets/imgs/register/delete.svg" alt=""
      /></span>
    </div>
    <div class="input-group">
      <input type="password" v-model="inputpassword" placeholder="请输入密码" />
      <span @click="emptyinputpassword($event)" v-if="inputpassword"
        ><img src="./../../assets/imgs/register/delete.svg" alt=""
      /></span>
    </div>
    <div class="input-group">
      <input
        type="password"
        v-model="inputpasswordagain"
        placeholder="请再次输入密码"
      />
      <span @click="emptyinputpasswordagain($event)" v-if="inputpasswordagain"
        ><img src="./../../assets/imgs/register/delete.svg" alt=""
      /></span>
    </div>

    <!-- 验证码 -->
    <div class="verify-group">
      <input type="text" v-model="verifyvalue" placeholder="验证码" />
      <span v-if="verifyvalue" style="right: 40%" @click="emptyverify($event)"
        ><img src="./../../assets/imgs/register/delete.svg" alt=""
      /></span>
      <button
        @click="getVerifyCode"
        :disabled="verifydisabled"
        :class="{ verifyactive: verifyActive }"
      >
        {{ btnTitle }}
      </button>
    </div>

    <!-- 注册按钮 -->
    <div class="log-btn">
      <button
        :disabled="registerdisabled"
        :class="{ registerActive: registerActive }"
        @click="handleregister()"
      >
        注册
      </button>
    </div>

    <!-- 用户协议 -->
    <div class="register-des">
      <label>
        <input
          type="checkbox"
          name="agreement"
          :checked="isChecked"
          @click="changeIsChecked"
        />
        <p>
          手机号注册后将自动生成账号，且代表你已经阅读并同意<span>《用户服务协议》</span>、<span
            >《隐私政策》</span
          >
        </p>
      </label>
    </div>

    <!-- 弹框 -->
    <div class="bounced" v-if="error">
      <div>{{ error }}</div>
    </div>
  </div>
</template>

<script>
import axios from '/src/request/index.js'
import HeaderNav from '/src/components/HeaderNav.vue'
export default {
  name: "Register",
  components: {
    HeaderNav,
  },
  data() {
    return {
      inputphone: "",
      inputpassword: "",
      inputpasswordagain: "",
      verifyvalue: "",
      verify: "",
      // 最开始禁用
      verifydisabled: true,
      registerdisabled: true,
      // 验证码样式verifyActive
      verifyActive: false,
      registerActive: false,
      // 错误信息
      error: "",
      btnTitle: "获取验证码",

      isChecked: false,
    };
  },
  methods: {
    bounceError(msg) {
      this.error = msg;
      setTimeout(() => {
        this.error = "";
      }, 2000);
    },
    // 清空输入框
    emptyinputphone(e) {
      // console.log(e.target.parentNode.parentNode.childNodes[0].value);
      // e.target.parentNode.parentNode.childNodes[0].value = "";
      this.inputphone = "";
    },
    emptyinputpassword(e) {
      // console.log(e.target.parentNode.parentNode.childNodes[0].value);
      // e.target.parentNode.parentNode.childNodes[0].value = "";
      this.inputpassword = "";
    },
    emptyinputpasswordagain(e) {
      // console.log(e.target.parentNode.parentNode.childNodes[0].value);
      // e.target.parentNode.parentNode.childNodes[0].value = "";
      this.inputpasswordagain = "";
    },
    emptyverify(e) {
      // e.target.parentNode.parentNode.childNodes[0].value = "";
      this.verifyvalue = "";
    },

    // 获取验证码
    getVerifyCode() {
      if (this.validatePhone()) {
        // 倒计时
        this.validateBth();
        // 发送请求
        axios.get('/user/valicode', {
          params: {
            mobile: this.inputphone
          }
        })
        .then((res) => {
          // console.log(res);
          this.verify = res.data.data.valicode;
        })
        .catch((err) => {
          console.log(err);
        })
      }
    },
    validateBth() {
      let time = 60;
      let timer = setInterval(() => {
        if (time == 0) {
          clearInterval(timer);
          this.btnTitle = "获取验证码";
          this.verifyActive = true;
        } else {
          this.btnTitle = "已发送(" + time + "s)";
          this.verifydisabled = true;
          this.verifyActive = false;
          time--;
        }
      }, 1000);
    },
    validatePhone() {
      // 验证手机号码
      if (!/^1[3456789]\d{9}$/.test(this.inputphone)) {
        this.bounceError("请填写合法的手机号");
        return false;
      } else {
        this.error = "";
        return true;
      }
    },
    validatepassword() {
        if (this.inputpassword.length < 6 || this.inputpassword.length > 18) {
            this.bounceError("密码长度需要在6-18之间");
            return false;
        } else if (this.inputpassword !== this.inputpasswordagain) {
            this.bounceError("两次输入密码不一致");
            return false;
        } else {
            this.error = "";
            return true;
        }
    },
    handleregister() {
      this.error = "";
      if(!this.validatepassword()) return;
      if(this.isChecked == false){
        this.bounceError("请勾选条款");
        return
      }
      axios.post("/user/register", {
        name: this.inputphone,
        pass: this.inputpassword,
        mobile: this.inputphone,
        })
        .then((res) => {
            //console.log(res);
            this.bounceError(res.data.message);
            // 校验并跳转
            if (this.verifyvalue === this.verify) {
            //localStorage.setItem("ele_register", true);
                if (res.data.code != -1) {
                  setTimeout(() => {
                    this.$router.push("/");
                  }, 2000);
                }
            } else {
                this.bounceError("验证码错误");
            }
        })
        .catch((err) => {
            console.log(err);
        });
    },
    changeIsChecked() {
      this.isChecked = !this.isChecked;
    },
  },
  watch: {
    // 如果 `inputphone` 发生改变，这个函数就会运行
    inputphone: function () {
      let oldinput = this.inputphone.slice(0, -1);
      if (this.inputphone.length > 11) {
        this.inputphone = this.inputphone.slice(0, 11);
      }
      if (this.inputphone != Number(this.inputphone)) {
        this.inputphone = oldinput;
      }
      if (this.inputphone.length == 11) {
        this.verifyActive = true;
        this.verifydisabled = false;
      } else {
        this.verifyActive = false;
        this.verifydisabled = true;
      }
      // if (this.verifyvalue.length >= 6 && String(this.verifyActive) == "true") {
      if (this.verifyvalue.length == 6 && this.inputphone.length == 11) {
        this.registerActive = true;
        this.registerdisabled = false;
      } else {
        this.registerActive = false;
        this.registerdisabled = true;
      }
    },
    inputpassword: function () {
      if (this.inputphone.length == 11) {
        this.verifyActive = true;
        this.verifydisabled = false;
      } else {
        this.verifyActive = false;
        this.verifydisabled = true;
      }
      if (this.verifyvalue.length == 6 && this.inputphone.length == 11) {
        this.registerActive = true;
        this.registerdisabled = false;
      } else {
        this.registerActive = false;
        this.registerdisabled = true;
      }
    },
    inputpasswordagain: function () {
      if (this.inputphone.length == 11) {
        this.verifyActive = true;
        this.verifydisabled = false;
      } else {
        this.verifyActive = false;
        this.verifydisabled = true;
      }
      if (this.verifyvalue.length == 6 && this.inputphone.length == 11) {
        this.registerActive = true;
        this.registerdisabled = false;
      } else {
        this.registerActive = false;
        this.registerdisabled = true;
      }
    },
    verifyvalue: function () {
      let verifyinput = this.verifyvalue.slice(0, -1);
      if (this.verifyvalue.length > 6) {
        this.verifyvalue = this.verifyvalue.slice(0, 6);
      }
      if (this.verifyvalue != Number(this.verifyvalue)) {
        this.verifyvalue = verifyinput;
      }
      if (this.verifyvalue.length == 6 && this.inputphone.length == 11) {
        this.registerActive = true;
        this.registerdisabled = false;
      } else {
        this.registerActive = false;
        this.registerdisabled = true;
      }
    },
  },
};
</script>

<style scoped>
.register {
  width: 100%;
  height: 100%;
  background-color: white;
}
.logo {
  text-align: center;
  padding-top: 50px;
}
.logo img {
  width: 200px;
  height: 200px;
  margin-top: 30px;
  margin-bottom: 20px;
}
/* 输入框样式 */
.input-group,
.verify-group {
  width: 80%;
  margin: 0 auto;
  position: relative;
}
.input-group input,
.verify-group input {
  width: 100%;
  height: 40px;
  border: none;
  border-bottom: 1px rgb(194, 193, 193) solid;
  caret-color: rgb(51, 151, 228);
  font-size: 16px;
  padding-left: 5px;
  margin-bottom: 10px;
}
.input-group input:focus,
.verify-group input:focus {
  outline: 0;
}

/* 输入框的删除 */
.input-group span,
.verify-group span {
  position: absolute;
  top: 15px;
  right: 0;
}
.input-group span img,
.verify-group span img {
  width: 13px;
}

/* 获取验证码按钮 */
.verify-group button {
  position: absolute;
  top: 10px;
  right: 0;
  width: 90px;
  height: 26px;
  border-radius: 13px;
  border: 1px solid rgb(194, 193, 193);
  color: rgb(194, 193, 193);
  background-color: white;
  font-size: 14px;
}
/* 注册按钮 */
.log-btn {
  width: 80%;
  margin: 0 auto;
}
.log-btn button {
  display: block;
  width: 100%;
  height: 30px;
  margin-top: 10px;
  margin-bottom: 10px;
  border-radius: 15px;
  border: 1px solid rgb(194, 193, 193);
  background-color: rgb(231, 231, 231);
}

/* 用户协议 */
.register-des {
  position: relative;
}
.register-des input {
  position: absolute;
  margin-top: 20px;
  left: 9%;
}
.register-des p {
  display: inline-block;
  font-size: 12px;
  /* text-indent:24px; */
  line-height: 15px;
  width: 75%;
  position: absolute;
  left: 15%;
}
.register-des p span {
  color: rgb(51, 151, 228);
}
.verify-group .verifyactive {
  border: 1px solid rgb(51, 151, 228);
  color: rgb(51, 151, 228);
}
.log-btn .registerActive {
  border: 1px solid rgb(51, 151, 228);
  background-color: rgb(51, 151, 228);
  color: white;
}

.bounced {
  position: fixed;
  width: 150px;
  height: 35px;
  background-color: rgba(0, 0, 0, 0.7);
  z-index: 9999;
  bottom: 200px;
  left: 125px;
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
