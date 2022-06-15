package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.common.exception.ApiAsserts;
import com.example.milkorder_backend.jwt.JwtUtil;
import com.example.milkorder_backend.mapper.UserMapper;
import com.example.milkorder_backend.model.dto.LoginDTO;
import com.example.milkorder_backend.model.dto.RegisterDTO;
import com.example.milkorder_backend.model.entity.User;
import com.example.milkorder_backend.service.IUserService;
import com.example.milkorder_backend.utils.MD5Utils;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import javax.annotation.Resource;
import java.util.Date;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class IUserServiceImpl extends ServiceImpl<UserMapper,User> implements IUserService {
    @Resource
    private IUserService iUserService;
    // 用户注册
    @Override
    public User executeRegister(RegisterDTO dto) {
        /**
         * 查询是否有相同用户名的用户
         */
        // 创建一个查询对象 wrapper，对应的的实体为 User
        LambdaQueryWrapper<User> wrapper = new LambdaQueryWrapper<>();
        // 将wrapper的username和email字段分别设为dto中传入的数据
        wrapper.eq(User::getUsername, dto.getName()).or().eq(User::getMobile, dto.getMobile());
        // 用wrapper中的值匹配一个实体User对象
        User User = baseMapper.selectOne(wrapper);
        if (!ObjectUtils.isEmpty(User)) {
            // 匹配成功说明已存在
            return null;
        }
        // 否者，创建一个新增对象addUser依次设置字段值，然后插入表单
        User addUser = User.builder()
                .username(dto.getName())
                .alias(dto.getName())
                .password(MD5Utils.getPwd(dto.getPass()))
                .mobile(dto.getMobile())
                .roleId(0)
                .avatar("https://img0.baidu.com/it/u=3577691567,3678877448&fm=26&fmt=auto&gp=0.jpg")
                .createTime(new Date())
                .status(true)
                .build();
        baseMapper.insert(addUser);

        return addUser;
    }

    // 通过用户名获取用户
    @Override
    public User getUserByUsername(String username) {
        // 同上
        return baseMapper.selectOne(new LambdaQueryWrapper<User>().eq(User::getUsername, username));
    }

    // 通过手机号获取用户
    @Override
    public User getUserByMobile(String mobile) {
        return baseMapper.selectOne(new LambdaQueryWrapper<User>().eq(User::getMobile, mobile));
    }

    // 用户登录
    @Override
    public String executeLogin(LoginDTO dto) {
        String token = null;
        try {
            User user = getUserByMobile(dto.getMobile());  // 获取输入手机号对应的用户对象
            String encodePwd = MD5Utils.getPwd(dto.getPassword());  // 将输入的密码MD5加密
            if(!encodePwd.equals(user.getPassword()))
            {
                throw new Exception("密码错误");
            }
            // 生成token
            token = JwtUtil.generateToken(String.valueOf(user.getUsername()));
        } catch (Exception e) {
            log.warn("用户不存在or密码验证失败=======>{}", dto.getMobile());
        }
        return token;
    }

    //  改密
    @Override
    public String changePassword(LoginDTO dto) {
        User user= getUserByMobile(dto.getMobile());
        if (ObjectUtils.isEmpty(user)){
            return "该号码未注册";
        }
        else {
            user.setPassword(MD5Utils.getPwd(dto.getPassword()));
            baseMapper.updateById(user) ;
            return "更改密码成功";
        }
    }

    // 支付
    @Override
    public Integer executePay(String cost, String userName) {
        User user = iUserService.getUserByUsername(userName);
        Integer balance = user.getBalance() - Integer.parseInt(cost);
        if (balance >= 0){
            baseMapper.updateBalance(balance,user.getId());
        }
        return balance;
    }

    // 充值
    @Override
    public Integer executeRecharge(String amount, String userName) {
        User user = iUserService.getUserByUsername(userName);
        Integer balance = user.getBalance() + Integer.parseInt(amount);
        baseMapper.updateBalance(balance,user.getId());
        return balance;
    }

    @Override
    public boolean changeAliasAndAvatar(String userName, String newAvatar, String newAlias) {
        User hasUser = baseMapper.selectOne(new LambdaQueryWrapper<User>().eq(User::getAlias, newAlias));
        if (!ObjectUtils.isEmpty(hasUser))
            return false;
        User user = iUserService.getUserByUsername(userName);
        if (ObjectUtils.isEmpty(newAvatar) && !ObjectUtils.isEmpty(newAlias))
            user.setAlias(newAlias);
        if (!ObjectUtils.isEmpty(newAvatar) && ObjectUtils.isEmpty(newAlias))
            user.setAvatar(newAvatar);
        if (!ObjectUtils.isEmpty(newAvatar) && !ObjectUtils.isEmpty(newAlias)){
            user.setAvatar(newAvatar);
            user.setAlias(newAlias);
        }
        baseMapper.updateById(user);
        return true;
    }
}
