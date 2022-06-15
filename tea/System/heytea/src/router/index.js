import {createRouter, createWebHistory} from 'vue-router';
import store from '/src/store/index.js';

const Home = () => import('/src/pages/home/Home.vue');
const Food = () => import('/src/pages/food/Food.vue');
const Shop = () => import('/src/pages/shop/Shop.vue');
const Order = () => import('/src/pages/order/Order.vue');
const Mine = () => import('/src/pages/mine/Mine.vue');
const Forget = () => import('/src/pages/forget/Forget.vue');
const Register = () => import('/src/pages/register/Register.vue');
const OrderDetail = () => import('/src/pages/orderDetail/OrderDetail.vue');
const OrderPay = () => import('/src/pages/orderPay/OrderPay.vue');
const SelectAddress = () => import('/src/pages/address/selectAddress/SelectAddress.vue');
const EditAddress = () => import('/src/pages/address/EditAddress.vue');
const AddAddress = () => import('/src/pages/address/AddAddress.vue');
const Place = () => import('/src/pages/place/Place.vue');
const Recharge = () => import('/src/pages/recharge/Recharge.vue');

const routes = [
    {path: '/', redirect: '/home'},
    {path: '/home', component: Home},
    {path: '/food', component: Food},
    {path: '/shop', component: Shop},
    {path: '/order', component: Order},
    {path: '/mine', component: Mine},
    {path: '/forget', component: Forget},
    {path: '/register', component: Register},
    {path: '/orderdetail', component: OrderDetail},
    {path: '/orderpay', component: OrderPay},
    {path: '/selectaddress', component: SelectAddress},
    {path: '/editaddress', component: EditAddress},
    {path: '/addaddress', component: AddAddress},
    {path: '/place', component: Place},
    {path: '/recharge', component: Recharge},
];

const router = createRouter({
    history: createWebHistory(),
    routes
});
const needLogin = ['/orderdetail', '/orderpay', '/selectaddress', '/editaddress', '/addaddress', '/recharge'];

router.beforeEach((to, from, next) => {
    if (needLogin.includes(to.path) && !store.state.isLogin) {
        setTimeout(() => {
            next({path: '/mine'});
        }, 1000)
    } else next();
});

export default router;