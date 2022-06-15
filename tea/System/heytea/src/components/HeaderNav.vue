<template>
    <div class="header_nav"><img src="/src/assets/imgs/common/back.png" @click="$router.back()" /><div id="insert"><slot></slot></div></div>
</template>

<script>
export default {
    name: 'HeaderNav',
}
</script>

<style scoped>
.header_nav {
  position: fixed;
  top: 0;
  height: 44px;
  width: 100%;
  line-height: 44px;
  text-align: center;
  color: #ffffff;
  z-index: 1;
  font-size: 19px;
  background: #666666;
}
.header_nav > img {
    width:25px;
    height: 25px;
    padding: 10px 0;
    float: left;
}
.header_nav #insert {
    display: inline-block;
    margin-left: -25px;
}
</style>