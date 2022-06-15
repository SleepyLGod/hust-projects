import {createStore} from 'vuex';
import getters from './getters';
import mutations from './mutations';
import actions from './actions';
import axios from '/src/request/index.js';

const state = {
    cartList: [],
    placeList: [],
    token: localStorage.getItem('token') ? localStorage.getItem('token') : '',
    isLogin: localStorage.getItem('token') ? true : false,
    addrNum: 0,
    orderNum: 0,
    classNum: 0,
    scrollNum: 0,
    place: {},
}
setTimeout(() => {
    axios.get('./store/list')
    .then((res) => {
        state.placeList = res.data.data.store;
        state.place = state.placeList[0];
        // console.log(state.place);
    })
    .catch((err) => {
        console.log(err);
    })
}, 0);

const store = createStore({
    state,
    getters,
    mutations,
    actions
})

export default store;