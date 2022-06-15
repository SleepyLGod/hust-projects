package com.example.milkorder_backend.model.dto;

import lombok.Data;
import org.hibernate.validator.constraints.Length;
import javax.validation.constraints.NotEmpty;
import java.util.List;

@Data
public class DrinkAddDTO {

    @NotEmpty(message = "请输入奶茶名称")
    @Length(min = 2, max = 15, message = "长度在2-15")
    private String name;

    @NotEmpty(message = "请输入奶茶价格")
    private String price;

    @NotEmpty(message = "请输入奶茶分类")
    @Length(min = 2, max = 10, message = "长度在2-10")
    private String cla;

    @NotEmpty(message = "请输入奶茶描述")
    @Length(min = 2, max = 300, message = "长度在2-300")
    private String describe;

    @NotEmpty(message = "请输入图片地址")
    private List<String> images;

    private List<String> tags;

}