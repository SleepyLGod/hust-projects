package com.example.milkorder_backend.model.entity;

import com.baomidou.mybatisplus.annotation.*;
import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.experimental.Accessors;
import org.apache.ibatis.javassist.SerialVersionUID;

import java.io.Serializable;
import java.util.Date;

@Data
@Builder
@TableName("drink")
@NoArgsConstructor
@AllArgsConstructor
@Accessors(chain = true)
public class Drink implements Serializable {

    private static final long serialVersionUID = 1032894099847211935L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private String id;

    @TableField("name")
    private String name;

    @TableField("price")
    private String price;

    @TableField("cla")
    private String cla;

    @TableField("is_hot")
    private Boolean isHot;

    @TableField("is_dairy")
    private Boolean isDairy;

    @TableField("is_recommend")
    private Boolean isRecommend;

    @TableField("des")
    private String des;


    @TableField("role_id")
    private Integer roleId;

    @JsonIgnore
    @TableField(value = "create_time", fill = FieldFill.INSERT)
    private Date createTime;

    @JsonIgnore
    @TableField(value = "modify_time", fill = FieldFill.INSERT_UPDATE)
    private Date modifyTime;

}