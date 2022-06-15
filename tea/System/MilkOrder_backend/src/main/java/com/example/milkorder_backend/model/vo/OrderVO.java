package com.example.milkorder_backend.model.vo;

import com.baomidou.mybatisplus.annotation.FieldFill;
import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.Builder;
import lombok.Data;

import java.util.Date;
import java.util.List;

@Data
@Builder
public class OrderVO {

    private String id;


    private String store;  // 所选店铺


    private String username;  // 下单者用户名


    private String delId;  // 收货信息的id


    private String code;  // 取单码


    private List<DrinkVO> drink;  // 所购奶茶


    private Integer drinkNum;  // 奶茶杯数


    private List<String> image;  // 奶茶杯数


    private String tipDes;  // 加料描述


    private String otherDes;  // 其他描述


    private String price;   // 总价格


    private Boolean isFinish;   // 订单是否已取


    private Boolean isTakeOut;   // 自取还是外卖（默认自取）

    private String createTime;

}
