package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.model.dto.LoginDTO;
import com.example.milkorder_backend.model.dto.RegisterDTO;
import com.example.milkorder_backend.model.entity.User;

public interface IUserService extends IService<User> {
    /**
     * 注册功能
     *
     * @param dto
     * @return 注册对象
     */
    User executeRegister(RegisterDTO dto);
    /**
     * 通过用户名获取用户信息
     *
     * @param username
     * @return dbUser
     */
    User getUserByUsername(String username);
    /**
     * 通过手机号获取用户信息
     *
     * @param mobile
     * @return dbUser
     */
    User getUserByMobile(String mobile);
    /**
     * 用户登录
     *
     * @param dto
     * @return 生成的JWT的token
     */
    String executeLogin(LoginDTO dto);
    /**
     * 改密
     * @param dto
     * @return
     */
    String changePassword(LoginDTO dto);

    /**
     * 支付
     * @param cost
     * @param userName
     * @return
     */
    Integer executePay(String cost,String userName);

    /**
     * 充值
     * @param amount
     * @param userName
     * @return
     */
    Integer executeRecharge(String amount, String userName);

    /**
     * 更改昵称和头像
     * @param userName
     * @param newAvatar
     * @param newAlias
     * @return
     */
    boolean changeAliasAndAvatar(String userName, String newAvatar, String newAlias);

}
