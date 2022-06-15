<template>
    <div id="shop">
        <div class="header"><div>喜茶百货</div></div>
        <!-- <div class="slider">
            <img src="/src/assets/imgs/shop/shop_slider.png" alt="">
        </div> -->
        <div class="slider">
            <swiper height="411px" :options="swiperOption" :list="swiperList" effect="normal" @onClick="handleSwiperClick"></swiper>
        </div>
        <div class="banner1">
            <div class="left">
                <p>喜茶瓶装</p>
                <div>随时随地喝喜茶<span> ❯</span></div>
                <img src="/src/assets/imgs/shop/shop_banner1_1.png" alt="">
            </div>
            <div class="right">
                <div class="up">
                    <div class="right_left">
                        <p>喜茶实验室</p>
                        <div>一周茶礼盒<span> ❯</span></div>
                    </div>
                    <img class="right_right" src="/src/assets/imgs/shop/shop_banner1_2.png" alt="">
                </div>
                <div class="bottom">
                    <div class="right_left">
                        <p>灵感周边</p>
                        <div>芝芝果茶杯<span> ❯</span></div>
                    </div>
                    <img class="right_right" src="/src/assets/imgs/shop/shop_banner1_3.png" alt="">
                </div>
            </div>
        </div>
        <div class="new">
            <p class="title">百货上新</p>
            <div class="desc">NEW ARRIVALS</div>
            <div class="banner"><img src="/src/assets/imgs/shop/shop_banner2.png" alt=""></div>
            <div class="item">
                <div class="left"><img src="/src/assets/imgs/shop/shop_banner2_item1.png" alt=""></div>
                <div class="right">
                    <p>喜茶果汁茶 6瓶入/12...</p>
                    <div>地中海桃桃金凤味/伊比...</div>
                    <span>¥ 48</span>
                    <button>立即购买</button>
                </div>
            </div>
            <div class="banner"><img src="/src/assets/imgs/shop/shop_banner3.png" alt=""></div>
            <div class="item" v-for="item in banner3_items" :key="item">
                <div class="left"><img :src="item.img" alt=""></div>
                <div class="right">
                    <p>{{item.title}}</p>
                    <div>{{item.tip}}</div>
                    <span>{{item.price}}</span>
                    <button>立即购买</button>
                </div>
            </div>
            <div class="banner"><img src="/src/assets/imgs/shop/shop_banner4.png" alt=""></div>
            <div class="item">
                <div class="left"><img src="/src/assets/imgs/shop/shop_banner4_item1.png" alt=""></div>
                <div class="right">
                    <p>灵感茗想茶礼盒 7款...</p>
                    <div>挂耳式茶包</div>
                    <span>¥ 59</span>
                    <button>立即购买</button>
                </div>
            </div>
        </div>
        <div class="guess">
            <p class="title">猜你喜欢</p>
            <div class="desc">YOU MAY ALSO LIKE</div>
            <div class="container">
                <div class="list" v-for="item in guess_item_list" :key="item">
                    <div class="item left">
                        <img :src="item.left.img" alt="">
                        <p>{{item.left.title}}</p>
                        <span>{{item.left.price}}</span>
                        <div>{{item.left.tip}}</div>
                        <button>+</button>
                    </div>
                    <div class="item right">
                        <img :src="item.right.img" alt="">
                        <p>{{item.right.title}}</p>
                        <span>{{item.right.price}}</span>
                        <div>{{item.right.tip}}</div>
                        <button>+</button>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import Swiper from '/src/components/Swiper.vue';
export default {
    name: "Shop",
    components: {
        Swiper
    },
    data() {
        return {
            swiperList: [
                '/src/assets/imgs/shop/shop_slider.png',
                '/src/assets/imgs/shop/shop_slider1.jpg',
                '/src/assets/imgs/shop/shop_slider2.jpg',
            ],
            swiperOption: {
                showDots: true,
                autoplay: true,
                interval: 2000,
                loop: true
            },
            banner3_items: [
                {img: '/src/assets/imgs/shop/shop_banner2_item1.png', title: '喜茶果汁茶 6瓶入/12...', price: "¥ 48", tip: "地中海桃桃金凤味/伊比..."},
                {img: '/src/assets/imgs/shop/shop_banner2_item1.png', title: '喜茶果汁茶 6瓶入/12...', price: "¥ 48", tip: "地中海桃桃金凤味/伊比..."},
                {img: '/src/assets/imgs/shop/shop_banner2_item1.png', title: '喜茶果汁茶 6瓶入/12...', price: "¥ 48", tip: "地中海桃桃金凤味/伊比..."},
                {img: '/src/assets/imgs/shop/shop_banner2_item1.png', title: '喜茶果汁茶 6瓶入/12...', price: "¥ 48", tip: "地中海桃桃金凤味/伊比..."},
                {img: '/src/assets/imgs/shop/shop_banner2_item1.png', title: '喜茶果汁茶 6瓶入/12...', price: "¥ 48", tip: "地中海桃桃金凤味/伊比..."},
            ],
            guess_item_list:[
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
                {
                    left: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                    right: {img: '/src/assets/imgs/shop/shop_banner4_item1.png', title: "喜茶 4口味混合装 无糖气哈哈哈航昂昂...", price: "¥ 66", tip: "2986人已购买"},
                },
            ],
        }
    },
    methods: {
        handleSwiperClick() {
            console.log(1);
        }
    }
}
</script>

<style scoped>
#shop {
    width: 100%;
    background-color: #FAFAFA;
}
#shop .header {
    position: fixed;
    top: 0px;
    height: 100px;
    width: 100%;
    z-index: 1;
    text-align: center;
    background-color: white;
}
#shop .header div {
    font-weight: 600;
    font-size: 18px;
    margin-top: 65px;
}
#shop .slider {
    margin-top: 100px;
}
/* #shop .slider img {
    width: 100%;
    height: 411px;
} */
#shop .banner1 {
    width: 92%;
    height: 180px;
    margin: 20px 4%;
}
#shop .banner1 .left {
    width: 33%;
    height: 165px;
    float: left;
    background-color: #F5F5F6;
    padding: 15px 15px 0;
    border-radius: 6px;
}
#shop .banner1 .left p {
    margin: 0;
    font-weight: 600;
    font-size: 16px;
    color: #3C3C3C;
}
#shop .banner1 .left div {
    width: 100px;
    margin: 10px 0 3px;
    font-size: 8px;
    padding: 2px;
    border: 1px solid rgb(189, 181, 181);
    border-radius: 3px;
    color: #878787;
}
#shop .banner1 .left img {
    width: 119px;
    height: 109px;
    margin-left: 3px;
}
#shop .banner1 .right {
    float: right;
    width: 55%;
}
#shop .banner1 .right>div {
    height: 80px;
    background-color: #F5F5F6;
}
#shop .banner1 .right>div .right_left {
    float: left;
    margin-left: 15px;
    margin-top: 16px;
}
#shop .banner1 .right>div .right_left p {
    margin: 0;
    font-weight: 600;
    font-size: 16px;
    color: #3C3C3C;
}
#shop .banner1 .right>div .right_left div {
    width: 73px;
    margin-top: 5px;
    font-size: 8px;
    padding: 2px;
    border: 1px solid rgb(189, 181, 181);
    border-radius: 3px;
    color: #878787;
}
#shop .banner1 .right>div img {
    width: 90px;
    height: 80px;
    float: right;
}
#shop .banner1 .right>.bottom {
    margin-top: 20px;
}
#shop .new {
    clear: both;
    width: 92%;
    margin: 35px 4% 0;
}
#shop .new .title {
    font-size: 18px;
    font-weight: 600;
    float: left;
    margin: 0;
    color: #4D4D4D;
}
#shop .new .desc {
    margin-left: 10px;
    font-weight: 400;
    margin-top: 7px;
    font-size: 12px;
    float: left;
    color: #B6B6B6;
}
#shop .new .banner {
    width: 100%;
    height: 166px;
    padding-top: 15px;
    clear: both;
    border-radius: 6px;
}
#shop .new .banner img {
    width: 100%;
    box-shadow: 0 0 5px #b9b5b5;
}
#shop .new .item {
    height: 155px;
    clear: both;
    margin: 3px;
    padding: 10px;
    background-color: white;
    border-radius: 6px;
    box-shadow: 0 0 5px #b9b5b5;
}
#shop .new .item .left {
    width: 45%;
    margin-left: 3px;
    float: left;
}
#shop .new .item .left img {
    width: 100%;
    height: 152px;
}
#shop .new .item .right {
    float: right;
}
#shop .new .item .right p {
    margin: 0;
    margin-top: 20px;
    font-weight: 600;
    color: #656565;
}
#shop .new .item .right div {
    font-size: 8px;
    margin: 5px 0;
    color: #878787;
}
#shop .new .item .right span {
    display: block;
    font-weight: 600;
    margin: 10px 0 10px;
}
#shop .new .item .right button {
    font-size: 12px;
    color: #FAF2E9;
    background-color: #DCAA74;
    padding: 5px 15px;
    border: none;
    border-radius: 20px;
}
#shop .guess {
    width: 92%;
    padding: 40px 4%
}
#shop .guess .title {
    font-size: 18px;
    font-weight: 600;
    float: left;
    margin: 0;
    margin-bottom: 18px;
    color: #4D4D4D;
}
#shop .guess .desc {
    margin-left: 10px;
    font-weight: 400;
    margin-top: 7px;
    font-size: 12px;
    float: left;
    color: #B6B6B6;
}
#shop .guess .container {
    width: 100%;
    clear: both;
    padding-bottom: 250px;
    margin-top: 10px;
}
#shop .guess .container .list {
    width: 100%;
    height: 265px;
}
#shop .guess .container .list .item {
    width: 48%;
    height: 265px;
    margin-top: 10px;
    background-color: white;
    border-radius: 6px;
}
#shop .guess .container .list .item img {
    width: 100%;
    height: 184px;
}
#shop .guess .container .list .item p {
    margin: 10px;
    margin-right: 0;
    width: 160px;
    white-space: nowrap;
    font-size: 14.5px;
    text-overflow: ellipsis;
    overflow: hidden;
}
#shop .guess .container .list .item span {
    font-size: 16px;
    font-weight: 600;
    float: left;
    margin-left: 10px;
}
#shop .guess .container .list .item div {
    margin-left: 5px;
    margin-top: 4px;
    font-size: 8px;
    float: left;
}
#shop .guess .container .list .item button {
    color: white;
    font-size: 22px;
    float: right;
    width: 25px;
    margin-right: 10px;
    height: 25px;
    border-radius: 50%;
    background-color: #DCAA74;
    border: none;
}
#shop .guess .container .list .left {
    float: left;
}
#shop .guess .container .list .right {
    float: right;
}
</style>