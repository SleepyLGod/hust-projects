package com.example.milkorder_backend.model.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.experimental.Accessors;

import java.io.Serializable;

@Data
@Builder
@TableName("drink_tag")
@NoArgsConstructor
@AllArgsConstructor
@Accessors(chain = true)
public class DrinkTag implements Serializable {
    private static final long serialVersionUID = 2471367855194634219L;

    @TableId(type = IdType.AUTO)
    private Integer id;

    @TableField("drink_id")
    private String drinkId;

    @TableField("tag_id")
    private String tagId;
}
