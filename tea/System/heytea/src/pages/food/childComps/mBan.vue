<template>
  <div>
    <div class="mBan"></div>
    <div class="main">
      <span class="close" @click="closeFn">X</span>
      <img :src="food['images'][0]" alt="" />
      <div class="text">
        <div class="name">{{ food.name }}</div>
        <span v-for="tag in food.tags" :key="tag">{{ tag }}</span>
        <p>产品描述</p>
        <p class="desc">{{ food.des }}</p>
      </div>
      <div class="bottom">
        <div class="price">￥{{ food.price }}</div>
        <div class="right">
          <span @click="subFood()">-</span>
          <div>{{count}}</div>
          <span @click="addFood()">+</span>
        </div>
      </div>
      <button @click="sure">确定</button>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    food: Object,
  },
  data() {
    return {
      count: 1,
    };
  },
  name: "mBan",
  methods: {
    closeFn() {
      this.count = 1;
      this.$emit("closeMban");
    },
    sure() {
      let foodNew = this.food;
      foodNew.addCount = this.count;
      this.$emit("addCart", foodNew);
      this.$emit("closeMban");
      this.count = 1;
    },
    addFood() {
      this.count++;
    },
    subFood() {
      if (this.count > 0) this.count--;
    },
  },
};
</script>


<style scoped>
.mBan {
  position: fixed;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
  z-index: 2;
  background-color: rgb(153, 152, 152);
  opacity: 0.3;
}
.main {
  width: 300px;
  height: 600px;
  background-color: #fff;
  position: fixed;
  z-index: 2;
  left: 50%;
  top: 55%;
  transform: translate(-50%, -50%);
  border-radius: 10px;
}
.main .close {
  position: absolute;
  right: 10px;
  top: 10px;
  width: 15px;
  height: 15px;
  line-height: 15px;
  background-color: rgb(134, 133, 133);
  text-align: center;
  font-size: 13px;
  border-radius: 100%;
  color: #fff;
}
.main .text {
  position: absolute;
  left: 10px;
  top: 170px;
  /* border-bottom: 0.2px solid rgb(155, 152, 152); */
}
.main .text .desc {
  max-width: 95%;
  max-height: 280px;
  overflow: scroll;
}
.main img {
  width: 80%;
  position: absolute;
  left: 10%;
  margin-top: 20px;
}
.main .name {
  font-size: 15px;
  color: rgb(10, 10, 10);
  margin-bottom: 5px;
}
.text span {
  display: inline-block;
  padding: 4px;
  background-color: rgb(224, 220, 220);
  font-size: 5px;
  margin-right: 10px;
}
.main p {
  font-size: 8px;
  color: rgb(124, 122, 122);
  margin-top: 5px;
}
.bottom {
  position: absolute;
  bottom: 70px;
  width: 100%;
}
.bottom div {
  display: inline-block;
}
.bottom .price {
  float: left;
  margin-left: 10px;
  font-size: 15px;
  color: rgb(10, 10, 10);
}
.bottom .right {
  float: right;
}
.right span {
  display: inline-block;
  width: 15px;
  height: 15px;
  line-height: 15px;
  border-radius: 100%;
  background-color: rgb(226, 128, 36);
  text-align: center;
  font-size: 20px;
  margin: 0px 5px 0 5px;
}
button {
  position: absolute;
  bottom: 20px;
  left: 50%;
  transform: translateX(-50%);
  display: inline-block;
  width: 270px;
  height: 30px;
  background-color: rgb(226, 128, 36);
  margin: 0 auto;
  border-radius: 4px;
  color: #fff;
}
</style>