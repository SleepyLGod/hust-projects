<template>
    <header-nav>添加地址</header-nav>
    <div id="address">
        <div class="item first_item">
            <p>联系人</p>
            <input type="text" class="line" v-model="addressForm.name" placeholder="请填写收货人姓名">
        </div>
        <div class="item">
            <p>性别</p>
            <input type="radio" class="circle" v-model="addressForm.sex" value="man">男士
            <input type="radio" class="circle second" v-model="addressForm.sex" value="woman">女士
        </div>
        <div class="item">
            <p>手机号</p>
            <input type="text" class="line" v-model="addressForm.phone" placeholder="请填写收货手机号码">
        </div>
        <div class="item">
            <p>收货地址</p>
            <input type="text" class="line" v-model="addressForm.address" placeholder="请填写收货地址">
        </div>
        <div class="item">
            <p>门牌号</p>
            <input type="text" class="line" v-model="addressForm.doorNum" placeholder="例：B座6楼602室">
        </div>
        <div class="footer">
            <input type="checkbox" v-model="addressForm.isDefault">
            <div>设置为默认地址</div>
        </div>
        <button class="sure" @click="sure">保存</button>
        <div class="bounced" v-if="error">
            <div>{{ error }}</div>
        </div>
    </div>
</template>

<script>
import HeaderNav from '/src/components/HeaderNav.vue';
import axios from '/src/request/index.js';
export default {
    name: 'AddAddress',
    components: {
        HeaderNav,
    },
    data() {
        return {
            error: '',
            addressForm: {
                name:"",
                sex:"man",
                phone:"",
                address:"",
                doorNum:"",
                isDefault:false
            }
        }
    },
    methods: {
        sure() {
            if (this.validateElse() && this.validatePhone()) {
                this.bounceError("编辑成功");
                let address = this.addressForm;
                // if (!this.$store.getters.getUser.address) this.$store.getters.getUser.address = [];
                // this.$store.getters.getUser.address.push(address);
                axios.post('/address/add', {
                    linkman: this.addressForm.name,
                    isMale: this.addressForm.sex === 'man' ? true : false,
                    mobile: this.addressForm.phone,
                    address: this.addressForm.address,
                    detail: this.addressForm.doorNum
                })
                .then((res) => {
                    // this.addressList = res.data.data;
                })
                .catch((err) => {
                    console.log(err);
                })
                setTimeout(() => this.$router.back(), 500);
            }
        },
        bounceError(msg) {
            this.error = msg;
            setTimeout(() => {
                this.error = "";
            }, 2000);
        },
        validateElse() {
            if(this.addressForm.name && this.addressForm.phone && this.addressForm.address && this.addressForm.doorNum) return true;
            this.bounceError('请完成未输入内容');
            return false;
        },
        validatePhone() {
            // 验证手机号码
            if (!/^1[345678]\d{9}$/.test(this.addressForm.phone)) {
                this.bounceError("请填写合法的手机号");
                return false;
            } else {
                this.error = "";
                return true;
            }
        },
    }
}
</script>

<style scoped>
#address {
  width: 96%;
  padding: 64px 2% 50px;
  background-color: #fff;
}
#address .first_item {
    border-top: 1px solid rgba(0, 0, 0, 0.1);
}
#address .item {
    width: 90%;
    padding: 20px;
    height: 20px;
    font-size: 14px;
    color: #666666;
    border-bottom: 1px solid rgba(0, 0, 0, 0.1);
}
#address .item > p {
    display: inline-block;
    width: 105px;
    color: black;
}
#address .item .line {
    width: 60%;
    border: none;
    outline: none;
    color: black;
    text-overflow: ellipsis;
}
#address .item .second {
    margin-left: 20px;
}
#address .footer {
    height: 20px;
    padding: 20px;
    font-size: 14px;
    color: #666666;
}
#address .footer > input {
    width: 14px;
    height: 14px;
}
#address .footer > div {
    display: inline-block;
    margin-left: 8px;
}
#address .sure {
    width: 90%;
    color: white;
    padding: 10px;
    margin: 30px 5% 0;
    font-size: 18px;
    background-color: #666666;
    border: none;
    border-radius: 10px;
}
#address .sure:active {
    background-color: orange;
}
#address .bounced {
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
#address .bounced div {
  line-height: 35px;
  color: white;
  text-align: center;
  font-size: 12px;
}
</style>