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
@TableName("tag")
@NoArgsConstructor
@AllArgsConstructor
@Accessors(chain = true)
public class Tag implements Serializable  {
    private static final long serialVersionUID = 890094961770319763L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private String id;

    @TableField("name")
    private String name;

    @JsonIgnore
    @TableField(value = "create_time", fill = FieldFill.INSERT)
    private Date createTime;

    @JsonIgnore
    @TableField(value = "modify_time", fill = FieldFill.INSERT_UPDATE)
    private Date modifyTime;
}
