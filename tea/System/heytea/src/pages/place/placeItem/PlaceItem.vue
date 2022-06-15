<template>
    <div id="placeItem">
        <div class="left">
            <p>{{place.name}}</p>
            <div>{{place.address}}</div>
        </div>
    </div>
</template>

<script>
export default {
    name: 'PlaceItem',
    props: {
        place: Object,
    },
    data() {
        return {
        }
    }
}
</script>

<style scoped>
#placeItem {
    width: 94%;
    height: 60px;
    padding: 20px 3%;
    background-color: white;
    margin-bottom: 20px;
}
#placeItem .left {
    float: left;
    line-height: 35px;
}
#placeItem .left > p {
    font-size: 16px;
    color: black;
}
#placeItem .left > div {
    font-size: 14px;
    color: #999999;
    max-width: 300px;
    height: 35px;
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
}
/* #placeItem > img {
    width: 24px;
    height: 24px;
    float: right;
    margin: 20px 15px;
} */
</style>