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
@TableName("del_address")
@NoArgsConstructor
@AllArgsConstructor
@Accessors(chain = true)
public class DelAddress implements Serializable {
    private static final long serialVersionUID = -3269344009886837258L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private String id;

    @JsonIgnore
    @TableField("user_id")
    private String  userId;   // 所属的用户ID

    @TableField("linkman")
    private String linkman;   // 联系人姓名

    @TableField("is_male")
    private Boolean isMale;   // 性别

    @TableField("mobile")
    private String mobile;   // 手机号

    @TableField("address")
    private String address;   // 大致地址

    @TableField("detail")
    private String detail;  // 门牌号

    @JsonIgnore
    @TableField(value = "create_time", fill = FieldFill.INSERT)
    private Date createTime;

    @JsonIgnore
    @TableField(value = "modify_time", fill = FieldFill.INSERT_UPDATE)
    private Date modifyTime;
}
