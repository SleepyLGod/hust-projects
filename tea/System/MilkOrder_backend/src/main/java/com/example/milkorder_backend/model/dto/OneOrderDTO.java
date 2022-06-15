package com.example.milkorder_backend.model.dto;

import lombok.AllArgsConstructor;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;

@Data
@AllArgsConstructor
public class OneOrderDTO {
    @NotBlank(message = "所购奶茶不能为空")
    @Size(min = 2, max = 15, message = "2到15位")
    private String drinkName;  // 所购奶茶

    @Size(min = 0, max = 100, message = "0到50位")
    private String tipDes;  // 加料描述

    @Size(min = 0, max = 100, message = "0到50位")
    private String otherDes;  // 其他描述

    private int drinkNum ; // 奶茶杯数
}
