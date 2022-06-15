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

@Builder
@Data
public class DrinkVO {

    private String id;


    private String name;


    private String price;

    private List<String> images;

    private List<String> tags;

    private String cla;


    private Boolean isHot;


    private Boolean isDairy;


    private Boolean isRecommend;


    private String des;

    private Integer num ;  // 杯数，订单时用

}
