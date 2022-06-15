<template>
  <div id="foodtop">
    <div class="h-input">
      <input type="text" placeholder="搜索文字" />
    </div>
    <div class="nav">
      <div class="nav-left">
        <span class="star"></span>
        <div @click="$router.push('/place')">{{$store.getters.getPlace.name}} ></div>
        <p>距离您3.1km</p>
      </div>
      <div class="nav-right">
        <div class="rl">自取</div>
        <div class="rr">外卖</div>
      </div>
    </div>
  </div>
</template>


<script>
export default {
  name: "foodTop",
};
</script>

<style scoped>
#foodtop {
  width: 100%;
  height: 121px;
  position: fixed;
  z-index: 1;
  background-color: #fff;
}
.h-input input {
  background-color: rgb(224, 220, 220);
  margin-left: 20px;
  border-radius: 10px;
  width: 250px;
  height: 25px;
  font-size: 10px;
  padding-left: 5px;
  margin-top: 10px;
}
.nav {
  margin: 10px;
  margin-top: 20px;
  height: 50px;
}
.nav-left {
  float: left;
}
.nav-left div {
  margin: 5px;
}
.nav-left p {
  color: rgb(170, 170, 170);
  font-size: 10px;
  margin-left: 5px;
  margin-bottom: 0;
}
.nav-right {
  float: right;
}
.nav-right .rl,
.rr {
  display: inline-block;
  width: 40px;
  height: 25px;
  line-height: 25px;
  background-color: black;
  text-align: center;
  font-size: 10px;
}
.nav-right .rl {
  border-top-left-radius: 10px;
  border-bottom-left-radius: 10px;
  color: #fff;
}

.nav-right .rr {
  background-color: rgb(224, 220, 220);
  border-top-right-radius: 10px;
  border-bottom-right-radius: 10px;
}
</style>