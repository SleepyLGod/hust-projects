<template>
    <div id="tabBarItem">
        <router-link :to="item.route" class='item'>
            <img v-if="route === item.route" :src="item.selected_img" alt="">
            <img v-else :src="item.img" alt="">
            <div>{{item.name}}</div>
        </router-link>
    </div>
</template>

<script>
import {useRoute} from 'vue-router'
export default {
    name: 'TabBarItem',
    props: {
        item: Object
    },
    computed: {
        route: () => {
            return useRoute().path
        }
    }
}
</script>

<style scoped>
.item {
    color: rgb(170, 170, 170);
    text-decoration: none;
}
.router-link-active {
    font-size: 12px;
    color: black;
    font-weight: 500;
}
.item img {
    width: 30px;
    height: 30px;
    margin-bottom: -2px;
}
.item div {
    margin: 0;
    font-size: 10px;
}
</style>