import axios from '/src/request/index.js';

const mutations = {
    ADDCART(state, info) {
        let goods = state.cartList.find(item => item.info.name === info.info.name);
        if (goods) {
            goods.count += info.info.addCount;
        } else {
            info.count = info.info.addCount;
            info.checked = true;
            state.cartList.push(info);
        }
    },
    DELETECART(state) {
        state.cartList.length = 0;
    },
    LOGIN(state, value) {
        state.token = value;
        localStorage.setItem('token', value);
        state.isLogin = true;
    },
    LOGOUT(state) {
        localStorage.removeItem('token');
        state.isLogin = false;
    },
    SELECTADDRNUM(state, num) {
        state.addrNum = num;
    },
    SELECTORDERNUM(state, num) {
        state.orderNum = num;
    },
    SETCLASSNUM(state, index) {
        state.classNum = index;
    },
    SETSCROLLNUM(state, index) {
        state.scrollNum = index;
    },
    SETPLACE(state, place) {
        state.place = place;
    }
}

export default mutations