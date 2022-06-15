<template>
    <div id="home">
      <div class="slider">
        <img src="./../../assets/imgs/home/home_slide.png" alt="">
      </div>
      <div class="way">
        <div class="up">
          <router-link class="left" to="/food">
            <img src="./../../assets/imgs/home/home_door.png" alt="">
            <p>门店自取</p>
            <div>下单免排队</div>
          </router-link>
          <div class="right">
            <img src="./../../assets/imgs/home/home_pickup.png" alt="">
            <p>外卖</p>
            <div>无接触配送，送喜到家</div>
          </div>
        </div>
        <div class="bottom">
          <img src="./../../assets/imgs/home/home_group_buying.png" alt="">
          <p>好友拼单</p>
          <div>拼单喝茶，分账更方便</div>
        </div>
      </div>
      <div class="banner">
        <div class="first">
          <p>喜茶百货</p>
          <div>果汁茶全新上市</div>
          <img src="./../../assets/imgs/home/home_nav1.png" alt="">
        </div>
        <div class="second">
          <p>阿喜团餐</p>
          <div>企业欢聚享福利</div>
          <img src="./../../assets/imgs/home/home_nav2.png" alt="">
        </div>
        <div class="third">
          <p>阿喜有礼</p>
          <div>初夏好礼即刻送</div>
          <img src="./../../assets/imgs/home/home_nav3.png" alt="">
        </div>
      </div>
      <div class="point">
        <div class="left">
          <p>我的积分</p>
          <span>0</span>
          <div>可兑换喜茶券和丰富灵感周边</div>
        </div>
        <div class="right">
          <img src="./../../assets/imgs/home/home_vipcode.png" alt="">
          <div>会员码</div>
        </div>
      </div>
    </div>
</template>

<script>
export default {
  name: 'Home'
}
</script>

<style scoped>
#home {
  width: 100%;
  height: 100%;
  background-color: whitesmoke;
}
#home .slider {
  width: 100%;
  height: 320px;
  padding-top: 50px;
}
#home .slider img {
  width: 100%;
  height: 300px;
}
#home .way {
  width: 90%;
  height: 200px;
  margin: -30px 5% 25px 5%;
  position: relative;
  border-radius: 10px;
  z-index: 1;
  background-color: white;
}
#home .way .up {
  display: flex;
  justify-items: center;
  align-items: center;
}
#home .way .up .left {
  flex: 1;
  width: 160px;
  padding: 12px;
  text-align: center;
  border-right: 1px solid rgb(233, 229, 229);
  text-decoration: none;
}
#home .way .up .left p {
  font-size: 18px;
  font-weight: 600;
  color: #646160;
  margin: 0 0 10px 0;
}
#home .way .up .left div {
  font-size: 12px;
  font-weight: 600;
  color: rgb(170, 170, 170);
}
#home .way .up .right {
  flex: 1;
  width: 160px;
  text-align: center;
  padding: 12px;
}
#home .way .up .right p {
  font-size: 18px;
  font-weight: 600;
  color: #646160;
  margin: 0 0 10px 0;
}
#home .way .up .right div {
  font-size: 12px;
  font-weight: 600;
  color: rgb(170, 170, 170);
}
#home .way .up .left img {
  width: 70px;
  height: 75px;
}
#home .way .up .right img {
  width: 70px;
  height: 75px;
}
#home .way .bottom {
  border-top: 1px solid rgb(233, 229, 229);
  padding-top: 8px;
  height: 20px;
  clear: both;
}
#home .way .bottom img {
  margin-left: 20px;
  margin-right: 10px;
  width: 30px;
  height: 28px;
  float: left;
}
#home .way .bottom p {
  margin: 4px 0 0 0;
  font-size: 15.5px;
  font-weight: 600;
  color: #646160;
  float: left;
}
#home .way .bottom div {
  float: right;
  font-size: 13px;
  font-weight: 600;
  margin-top: 4px;
  margin-right: 15px;
  color: rgb(170, 170, 170);
}
#home .banner {
  width: 90%;
  height: 110px;
  margin-left: 5%;
  margin-bottom: 20px;
  display: flex;
}
#home .banner>div {
  flex: 1;
  vertical-align: middle;
  padding: 10px 8px 0 8px;
  position: relative;
  border-radius: 8px;
}
#home .banner .first {
  background-color: #E3EAEE;
}
#home .banner .second {
  background-color: #EFE9DD;
  margin: 0 9px;
}
#home .banner .third {
  background-color: #F0E6DF;
}
#home .banner>div p {
  font-size: 15.5px;
  margin: 0;
  font-weight: 600;
  color: #646160;
  margin-bottom: 3px;
}
#home .banner>div div {
  font-size: 8px;
  color: rgb(170, 170, 170);
}
#home .banner>div img {
  width: 80%;
  height: 50px;
  position: absolute;
  bottom: 0;
  margin-left: 5px;
}
#home .point {
  width: 90%;
  height: 80px;
  margin-left: 5%;
  padding-top: 10px;
}
#home .point>div {
  display: inline-block;
}
#home .point .left {
  float: left;
  padding-left: 10px;
}
#home .point .left p {
  font-size: 15.5px;
  font-weight: 600;
  margin: 0;
  color: #646160;
  display: inline-block;
}
#home .point .left span {
  font-weight: 700;
  color: #646160;
  display: inline-block;
  margin-left: 10px;
}
#home .point .left div {
  font-size: 12.5px;
  font-weight: 600;
  margin-top: 8px;
  color: rgb(170, 170, 170);
}
#home .point .right {
  float: right;
  margin-right: 10px;
  padding-left: 15px;
  border-left: rgb(233, 229, 229) 1px solid;
  text-align: center;
}
#home .point .right img{
  width: 35px;
  height: 35px;
}
#home .point .right div {
  margin-top: -5px;
  font-size: 12px;
  font-weight: 600;
  color: rgb(170, 170, 170);
}
</style>