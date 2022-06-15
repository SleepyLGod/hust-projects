<template>
  <div class="fooditems">
    <div
      v-for="(item, index) in classList"
      :key="index"
      class="foodItem"
      :class="{ foodItemActive: currentIndex === index }"
      @click="change(index)"
    >
      <p>{{ item.name }}</p>
    </div>
  </div>
</template>

<script>
import axios from '/src/request/index.js';
export default {
  name: "foodItems",
  created() {
    axios.get('/cla/list', {})
    .then((res) => {
      // console.log(res);
        this.classList = res.data.data.class;
    })
    .catch((err) => {
        console.log(err);
    });
  },
  data() {
    return {
      classList: [],
    };
  },
  computed: {
    currentIndex() {
      return this.$store.getters.getScrollNum;
    }
  },
  methods: {
    change(index) {
      this.$store.commit('SETCLASSNUM', index);
    },
  },
};
</script>

<style scoped>
.fooditems {
  position: fixed;
  top: 121px;
  bottom: 0;
  left: 0;
  right: 80%;
  padding-bottom: 100px;
  font-size: 10px;
  color: #8f8c8c;
  background-color: rgba(0, 0, 0, 0.05);
  overflow: scroll;
}
.foodItem {
  width: 94%px;
  line-height: 60px;
  text-align: left;
  padding-left: 5px;
}
.foodItemActive {
  border-left: 5px solid rgb(218, 120, 29);
  background-color: white;
}
</style>