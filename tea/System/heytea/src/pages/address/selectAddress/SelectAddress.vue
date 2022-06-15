<template>
    <header-nav>选择地址</header-nav>
    <div id="selectAddress">
        <address-item
        :class="{ isActive: AddrNum === index }"
        v-for="(address, index) in addressList"
        :key="address"
        :address="address"
         @click="selectAddr(index)"
         >
         </address-item>
        <button class="footer" @click="$router.push('/addaddress')">添加地址</button>
    </div>
</template>

<script>
import AddressItem from './addressItem/AddressItem.vue';
import HeaderNav from '/src/components/HeaderNav.vue';
import axios from '/src/request/index.js';
export default {
    name: 'SelectAddress',
    components: {
        AddressItem,
        HeaderNav,
    },
    beforeMount() {
        axios.get('/address/list')
        .then((res) => {
            this.addressList = res.data.data;
        })
        .catch((err) => {
            console.log(err);
        })
    },
    data() {
        return {
            addressList: [],
            AddrNum: -1,
        }
    },
    methods: {
        selectAddr(num) {
            this.AddrNum = num;
            this.$store.commit('SELECTADDRNUM', num);
        }
    }
}
</script>

<style scoped>
#selectAddress {
    padding: 44px 0 0;
    background-color: #f5f5f5;
    min-height: 95%;
}
.isActive {
    box-shadow: 0 3px 3px rgba(0, 0, 0, 0.1);
}
#selectAddress .footer {
    margin: 100px 10% 0;
    width: 80%;
    height: 40px;
    border-radius: 6px;
    border: none;
    color: white;
    background-color: #666666;
}
</style>