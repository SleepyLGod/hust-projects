package com.example.milkorder_backend.model.dto;

import com.baomidou.mybatisplus.annotation.TableField;
import lombok.AllArgsConstructor;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;
import java.util.List;
import java.util.Map;

@Data
public class OrderDTO {

    @NotBlank(message = "所选店铺不能为空")
    @Size(min = 2, max = 30, message = "2到30位")
    private String store;  // 所选店铺

    @NotBlank(message = "收货信息不能为空")
    private String delId;  // 下单者联系电话

    private boolean isTakeOut ; // 是否外卖

    private List<OneOrderDTO> products;

}

