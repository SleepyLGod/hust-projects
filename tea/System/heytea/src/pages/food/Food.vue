<template>
  <div class="food">
    <food-top />
    <food-items class="fooditems"/>
    <foods class="foods" @addMban="add" />
    <m-ban
      v-if="MbanShow"
      :food='food'
      @addCart="addCart"
      @closeMban="closeMban"
    />
    <food-cart
      :food='food'
    />
  </div>
</template>

<script>
import FoodCart from "./childComps/foodCart.vue";
import FoodItems from "./childComps/foodItems.vue";
import Foods from "./childComps/foods.vue";
import foodTop from "./childComps/foodTop.vue";
import MBan from "./childComps/mBan.vue";
export default {
  name: "Food",
  components: {
    foodTop,
    FoodItems,
    Foods,
    MBan,
    FoodCart,
  },
  data() {
    return {
      food: {},
      foodactive: false,
      MbanShow: false,
    };
  },
  methods: {
    add(food) {
      this.food = food;
      this.MbanShow = true;
    },
    closeMban() {
      this.MbanShow = false;
    },
    addCart(food) {
      this.$store.dispatch("addcart", food);
    },
  },
};
</script>

<style scoped>
.food {
  /* height: 100%; */
  position: absolute;
  top: 0;
  bottom: 50px;
  right: 0;
  left: 0;
}
</style>