<template>
    <div id="addressItem">
        <div class="left">
            <p>{{address.linkman}}（{{sex}}） {{address.mobile}}</p>
            <div>{{address.address}} {{address.detail}}</div>
        </div>
        <img src="/src/assets/imgs/address/edit.png" alt="" @click="$router.push('/editaddress')" >
    </div>
</template>

<script>
export default {
    name: 'AddressItem',
    props: {
        address: Object,
    },
    data() {
        return {
            sex: this.address.isMale === true ? '先生' : '女士',
        }
    }
}
</script>

<style scoped>
#addressItem {
    width: 94%;
    height: 60px;
    padding: 20px 3%;
    background-color: white;
    margin-bottom: 20px;
}
#addressItem .left {
    float: left;
    line-height: 35px;
}
#addressItem .left > p {
    font-size: 16px;
    color: black;
}
#addressItem .left > div {
    font-size: 14px;
    color: #999999;
    max-width: 300px;
    text-overflow: ellipsis;
}
#addressItem > img {
    width: 24px;
    height: 24px;
    float: right;
    margin: 20px 15px;
}
</style>