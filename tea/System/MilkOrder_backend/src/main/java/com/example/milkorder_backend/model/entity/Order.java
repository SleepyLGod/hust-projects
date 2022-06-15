package com.example.milkorder_backend.model.entity;

import com.baomidou.mybatisplus.annotation.*;
import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.experimental.Accessors;

import java.io.Serializable;
import java.util.Date;

@Data
@Builder
@TableName("drink_order")
@NoArgsConstructor
@AllArgsConstructor
@Accessors(chain = true)
public class Order implements Serializable {

    private static final long serialVersionUID = -5749344487125778279L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private String id;

    @TableField("store")
    private String store;  // 所选店铺

    @TableField("username")
    private String username;  // 下单者用户名

    @TableField("del_id")
    private String delId;  // 收货信息的id

    @TableField("code")
    private String code;  // 取单码

    @TableField("drink_name")
    private String drinkName;  // 所购奶茶

    @TableField("drink_num")
    private String drinkNum;  // 奶茶杯数

    @TableField("tip_des")
    private String tipDes;  // 加料描述

    @TableField("other_des")
    private String otherDes;  // 其他描述

    @TableField("price")
    private String price;   // 总价格

    @TableField("is_finish")
    private Boolean isFinish;   // 订单是否已取

    @TableField("is_take_out")
    private Boolean isTakeOut;   // 自取还是外卖（默认自取）

    @TableField(value = "create_time", fill = FieldFill.INSERT)
    private Date createTime;

    @JsonIgnore
    @TableField(value = "modify_time", fill = FieldFill.INSERT_UPDATE)
    private Date modifyTime;
}
