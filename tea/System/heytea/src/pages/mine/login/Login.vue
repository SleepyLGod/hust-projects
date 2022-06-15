<template>
    <div v-if="show" id="login">
        <div class="login-box">
            <div class="login-box-inner">
                <div class="login-title">登录</div>
                <div class="login-content">请输入您的账号和密码</div>
                <div class="login-input">
                    <span>账号</span><input type="text" class="username" v-model="inputphone" /><br>
                    <span>密码</span><input type="password" class="password" v-model="inputpassword" />
                </div>
            </div>
            <div class="login-box-buttons">
                <router-link to="/forget" class="forget">忘记密码</router-link>
                <router-link to="/register" class="register">注册</router-link>
                <span class="login-btn-success" @click="success">确定</span>
                <span class="login-btn-cancel" @click="cancel">取消</span>
            </div>
        </div>

        <div class="bounced" v-if="error">
            <div>{{ error }}</div>
        </div>
    </div>
</template>
<script>
import axios from '/src/request/index.js'
export default {
    name: 'Login',
    data () {
        return {
            inputphone: '',
            inputpassword: '',
            error: '',
            show: false,
        }
    },
    methods: {
        bounceError(msg) {
            this.error = msg;
            setTimeout(() => {
                this.error = "";
            }, 2000);
        },
        validatePhone() {
            // 验证手机号码
            if (this.inputphone === '') {
                this.bounceError("请输入手机号");
            } else if (!/^1[3456789]\d{9}$/.test(this.inputphone)) {
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
            } else {
                this.error = "";
                return true;
            }
        },
        open() {
            this.show = true;
        },
        success() {
            //this.show = false;
            if (this.validatePhone() && this.validatepassword()) {
                axios.post('/user/login', {
                    mobile: this.inputphone,
                    password: this.inputpassword
                })
                .then((res) => {
                    this.bounceError(res.data.message);
                    if (res.data.code == 200) {
                        this.$store.dispatch('login', res.data.data.token);
                        setTimeout(() => {
                            this.show = false;
                        }, 1500);
                    }
                })
                .catch((err) => {
                    console.log(err);
                })
            }
        },
        cancel() {
            this.show = false;
            this.inputphone = '';
            this.inputpassword = '';
        }
    }
}
</script>
<style scoped>
#login {
    background: rgba(00, 00, 00, 0.5);
    position: fixed;
    left: 0;
    top: 0;
    width: 100%;
    height: 100%;
    z-index: 9;
}
#login .login-box {
    width: 80%;
    max-width: 400px;
    top: 200px;
    position: absolute;
    left: 0;
    right: 0;
    margin: auto;
    background: #fff;
    box-sizing: border-box;
    padding: 20px;
    border-radius: 6px;

}
#login .login-box .login-box-inner .login-title {
    padding-left: 10px;
    margin-bottom: 0;
    font-size: 18px;
    font-weight: 700;
    height: 18px;
    color: #333;
}
#login .login-box .login-box-inner .login-content {
    padding: 10px 0 0 10px;
    line-height: 24px;
    color: #48576a;
    font-size: 12px;
}
#login .login-box .login-box-inner .login-input {
    padding: 10px;
    text-align: left;
    line-height: 40px;
}
#login .login-box .login-box-inner .login-input span {
    color: #333;
    font-size: 14px;
}
#login .login-box .login-box-buttons {
    display: flex;
    align-items: center;
    /* justify-items: center; */
    /* align-content: space-around; */
    justify-content: space-between;
}
#login .login-box .login-box-buttons .forget {
    flex: 1;
    font-size: 14px;
    color: #48576a;
    /* margin: 0 10px; */
    text-decoration: none;
}
#login .login-box .login-box-buttons .register {
    flex: 1;
    font-size: 14px;
    color: #48576a;
    /* margin: 0 10px; */
    text-decoration: none;
}
#login .login-box .login-box-buttons .login-btn-success {
    flex: 0;
    background: #20a0ff;
    border-color: #20a0ff;
    display: inline-block;
    line-height: 1;
    white-space: nowrap;
    cursor: pointer;
    color: #fff;
    /* margin: 0 5px 0 30px; */
    padding: 10px 15px;
    border-radius: 4px;
}
#login .login-box .login-box-buttons .login-btn-cancel {
    flex: 0;
    display: inline-block;
    line-height: 1;
    white-space: nowrap;
    cursor: pointer;
    background: #fff;
    border: 1px solid #c4c4c4;
    color: #1f2d3d;
    /* margin: 0; */
    padding: 10px 15px;
    border-radius: 4px;
}
#login .bounced {
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
#login .bounced div {
  line-height: 35px;
  color: white;
  text-align: center;
  font-size: 12px;
}
</style>
