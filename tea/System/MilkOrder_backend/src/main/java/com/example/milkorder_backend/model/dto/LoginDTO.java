package com.example.milkorder_backend.model.dto;

import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;

@Data
public class LoginDTO {

    @NotBlank(message = "手机号不能为空")
    @Size(min = 11, max = 11, message = "号码格式11位")
    private String mobile;

    @NotBlank(message = "密码不能为空")
    @Size(min = 6, max = 20, message = "登录密码长度在6-20")
    private String password;

    private Boolean rememberMe;
}
