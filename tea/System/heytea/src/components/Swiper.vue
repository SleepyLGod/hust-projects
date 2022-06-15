<template>
  <div class="swiper-component" @touchstart="onTouchStart" @touchend="onTouchEnd" :style="{height:height}">
    <ul :style="[ulStyle, swiperStyle]">
      <li v-for="(item, ind) in list" :key="ind" :style="{width: itemWidth + 'px'}" :class="[index===ind?'active':'', effect]" @click="handleClick(item)">
        <img :src="item">
      </li>
    </ul>
    <div v-show="options.showDots" class="swiper-dots">
      <div v-for="(item, ind) in list" :key="ind" class="dots-item" :class="{active:index===ind}"></div>
    </div>
  </div>
</template>

<script>
export default {
    name: 'Swiper',
  data() {
    return {
      ulStyle: { width: "750px", paddingLeft: "20px" }, // 轮播图容器宽度
      itemWidth: 750, // 单个轮播图容器的宽度，默认屏幕宽度,
      swiperStyle: {}, // 控制轮播的样式
      index: 0, // 当前显示的轮播图索引，默认第一张
      touchStart: {}, // 触摸开始点位
      touchEnd: {}, // 触摸结束点位
      intervalTime: "" // 循环轮播定时器
    };
  },
  props: {
    height: {
      type: String,
      default: "3rem"
    },
    options: {
      type: Object,
      default: {
        showDots: true, // 是否显示分页器
        interval: 3000, // 轮播间隔时间，默认3s
        autoplay: true, // 是否自动播放
        loop: false // 是否循环轮播
      }
    },
    list: {
      type: Array,
      default: []
    },
    effect: {
      type: String,
      default: "zoom" // 轮播图的样式类型，默认正常类型 normal，可选：zoom（缩放）
    }
  },
  created() {
    if (this.effect === "normal") {
      // 如果是正常模式，一张图的宽度为屏幕宽度
      this.itemWidth = document.body.clientWidth; // 获取屏幕的宽度
    } else if (this.effect === "zoom") {
      // 如果是缩放模式，控制轮播图显示的宽度，两边流出空隙
      this.itemWidth = document.body.clientWidth - 40; // 获取屏幕的宽度
    }
    this.handleType();
    var length = this.list.length; // 获取列表的个数
    this.ulStyle.width = parseInt((this.itemWidth + 40) * length) + "px"; // 容器总宽度
  },
  mounted() {
    this.handleLoopMove();
  },
  methods: {
    /**
     * 判断轮播类型，根据类型执行对应的操作
     */
    handleType() {
      if (this.effect === "normal") {
        this.ulStyle.paddingLeft = 0; // 将起始位置左侧的padding置为0
      } else if (this.effect === "zoom") {
        this.ulStyle.paddingLeft = "20px"; // 保证左侧有一定的位移
      }
    },
    /**
     * 移动处理
     */
    handleMove() {
      let moveX = this.itemWidth * this.index;
      if (this.index === 0) {
        moveX = 0;
        this.handleType();
      } else {
        this.ulStyle.paddingLeft = 0; // 将起始位置左侧的padding置为0
        if (this.effect === "zoom") {
          moveX = moveX - 20;
        }
      }
      this.swiperStyle = {
        transform: "translateX(-" + moveX + "px)"
      };
    },
    /**
     * 循环移动处理
     */
    handleLoopMove() {
      // 当设置自动播放时，执行自动循环播放操作，否则，只执行下一次轮播效果
      if (this.options.autoplay) {
        let interval = this.options.interval ? this.options.interval : 3000; 
        this.intervalTime = setInterval(() => {
          this.index++;
          if (this.index > this.list.length - 1) {
            this.index = 0; // 置为-1,下次轮播时index就会变成0，图片定位到起始位置
          }
          this.handleMove();
        }, interval);
      }
    },
    /**
     * 触摸开始事件，记录下触摸点
     */
    onTouchStart(e) {
      this.touchStart = e.changedTouches[0]; // 记录开始触摸点
      // 清楚定时器
      clearInterval(this.intervalTime);
    },
    /**
     * 触摸结束事件，记录下触摸点，比较当前点和触摸开始点，判断触摸方向
     */
    onTouchEnd(e) {
      this.touchEnd = e.changedTouches[0];
      // 比较移动的点位差，正数就是右滑，负数就是左滑
      if (this.touchEnd.clientX - this.touchStart.clientX > 60) {
        this.index--;
        if (this.index <= 0) {
          this.index = 0;
        }
      } else if (this.touchEnd.clientX - this.touchStart.clientX < -60) {
        this.index++;
        if (this.index >= this.list.length - 1) {
          this.index = this.list.length - 1;
        }
      }
      // 处理当前的滑动
      this.handleMove();
      // 同时开启自动轮播
      this.handleLoopMove();
    },
    handleClick(item) {
      this.$emit('onClick');
    }
  }
};
</script>

<style lang="less" scoped>
.swiper-component {
  overflow: hidden;
  height: 3rem;
  position: relative;
  ul {
    white-space: nowrap;
    height: 100%;
    transition: 0.5s ease;
    li {
      list-style: none;
      height: 100%;
      float: left;
      overflow: hidden;
      img {
        width: 100%;
        height: 100%;
      }
      &.zoom {
        border-radius: 0.16rem;
        transform: scale(0.93);
        transition: 0.5s ease;
        &.active {
          transform: scale(1);
        }
      }
    }
  }
  .swiper-dots {
    position: absolute;
    bottom: 0.16rem;
    left: 50%;
    transform: translateX(-50%);
    display: flex;
    .dots-item {
      width: 0.1rem;
      height: 0.1rem;
      border-radius: 50%;
      background: rgba(255, 255, 255, 0.7);
      margin: 0rem 0.04rem;
      &.active {
        background: #409eff;
      }
    }
  }
}
</style>