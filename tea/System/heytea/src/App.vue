<template>
    <div id="app">
      <router-view></router-view>
      <main-tab-bar v-show="mainIndex"></main-tab-bar>
    </div>
</template>

<script>
import MainTabBar from './components/MainTabBar.vue'
import {useRoute} from 'vue-router'
export default {
  name: 'app',
  components: {
    MainTabBar
  },
  data() {
    return {
      mainRoutes: ['/home', '/food', '/shop', '/order', '/mine']
    }
  },
  computed: {
    mainIndex() {
      return this.mainRoutes.includes(useRoute().path);
    }
  }
}
</script>

<style>
    @import './assets/css/common.css';
</style>

