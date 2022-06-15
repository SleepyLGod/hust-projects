<template>
    <div id="mainTabBar">
        <div v-for="item in items" class="item" :key="item.name">
            <tab-bar-item :item="item"></tab-bar-item>
        </div>
    </div>
</template>

<script>
import TabBarItem from './TabBarItem.vue'
export default {
    name: 'MainTabBar',
    components: {
        TabBarItem
    },
    data() {
        return {
            items: [
            {img: './src/assets/imgs/tabbar/home.png', selected_img: './src/assets/imgs/tabbar/home_active.png', name: '首页', route: '/home'},
            {img: './src/assets/imgs/tabbar/food.png', selected_img: './src/assets/imgs/tabbar/food_active.png', name: '点单', route: '/food'},
            {img: './src/assets/imgs/tabbar/shop.png', selected_img: './src/assets/imgs/tabbar/shop_active.png', name: '百货', route: '/shop'},
            {img: './src/assets/imgs/tabbar/order.png', selected_img: './src/assets/imgs/tabbar/order_active.png', name: '订单', route: '/order'},
            {img: './src/assets/imgs/tabbar/mine.png', selected_img: './src/assets/imgs/tabbar/mine_active.png', name: '我的', route: '/mine'},
        ],
        }
    },
}
</script>

<style scoped>
#mainTabBar {
    width: 100%;
    height: 49px;
    border-top: 1px solid #eee;
    box-shadow: 0px -1px 1px rgb(150 150 150 / 8%);
    position: fixed;
    bottom: 0;
    left: 0;
    right: 0;
    background-color: #f6f6f6;
    display: flex;
    justify-items: center;
    text-align: center;
    z-index: 99;
}
#mainTabBar .item {
    flex: 1;
}
</style>