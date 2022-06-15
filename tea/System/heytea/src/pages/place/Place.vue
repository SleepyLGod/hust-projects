<template>
    <header-nav>选择门店</header-nav>
    <div id="place">
        <div class="top">
            <div class="choose">
                <div :class="{ selected: isSelected }" @click="selectFirst">选择门店</div>
                <div :class="{ selected: !isSelected }" @click="selectSecond">常用/收藏</div>
            </div>
            <div class="position">
                <div class="left">武汉市 全部地区 <span>></span></div>
                <div class="right">
                    <img src="/src/assets/imgs/place/search.png" alt="">
                    搜索
                </div>
            </div>
        </div>
        <img class="map" src="/src/assets/imgs/place/map.jpg" alt="">
        <div class="item">
            <place-item v-for="(place, index) of placeList"
            :key="place"
            :class="{ isActive: placeNum === index }"
            :place="place"
            @click="selectPlace(index)">
            </place-item></div>
    </div>
</template>

<script>
import PlaceItem from './placeItem/PlaceItem.vue';
import HeaderNav from '/src/components/HeaderNav.vue';
export default {
    name: 'Place',
    components: {
        PlaceItem,
        HeaderNav,
    },
    data() {
        return {
            isSelected: true,
            placeNum: 0,
        }
    },
    beforeMount() {
        this.placeList = this.$store.getters.getPlaceList;
    },
    methods: {
        selectFirst() {
            this.isSelected = true;
        },
        selectSecond() {
            this.isSelected = false;
        },
        selectPlace(index) {
            this.placeNum = index;
            this.$store.commit('SETPLACE', this.placeList[index]);
        }
    }
}
</script>

<style scoped>
#place {
    padding: 0;
    background-color: #f5f5f5;
    height: 90%;
}
.top {
    padding-top: 50px;
    width: 100%;
    height: 100px;
}
.top .choose {
    display: flex;
    height: 50px;
    line-height: 50px;
    border-bottom: 1px solid rgba(0, 0, 0, 0.05);
}
.top .choose > div {
    text-align: center;
    flex: 1;
    color: #666666;
}
.top .choose .selected {
    color: rgb(219,168,113);
    border-bottom: 2px solid rgb(219,168,113);
}
.top .position {
    width: 100%;
    height: 50px;
    padding-top: 20px;
}
.top .position .left {
    float: left;
    font-size: 15px;
    margin-left: 15px;
}
.top .position .right {
    float: right;
    background-color: rgba(0, 0, 0, 0.1);
    width: 60px;
    height: 30px;
    font-size: 12px;
    color: #666666;
    margin-right: 20px;
    text-align: center;
    border-radius: 20px;
}
.top .position .right > img {
    width: 15px;
    height: 15px;
    margin-top: 7px;
    margin-right: 3px;
}
.map {
    width: 94%;
    padding: 20px 3%;
}
.item {
    width: 100%;
    height: 50%;
    overflow: scroll;
}
.isActive {
    box-shadow: 0 3px 3px rgba(0, 0, 0, 0.1);
}
</style>