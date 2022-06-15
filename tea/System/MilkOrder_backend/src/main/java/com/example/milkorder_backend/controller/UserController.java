package com.example.milkorder_backend.controller;

import com.example.milkorder_backend.common.api.ApiResult;
import com.example.milkorder_backend.jwt.JwtUtil;
import com.example.milkorder_backend.model.dto.LoginDTO;
import com.example.milkorder_backend.model.dto.RegisterDTO;
import com.example.milkorder_backend.model.entity.DelAddress;
import com.example.milkorder_backend.model.entity.User;
import com.example.milkorder_backend.service.IDelAddressService;
import com.example.milkorder_backend.service.IDrinkImageService;
import com.example.milkorder_backend.service.IUserService;
import com.example.milkorder_backend.utils.SendMessageUtils;
import org.springframework.util.ObjectUtils;
import org.springframework.web.bind.annotation.*;


import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.*;

@RestController
@RequestMapping("/user")
public class UserController {
    @Resource
    private IUserService iUserService;

    @Resource
    private IDelAddressService iDelAddressService;

    /**
     * 注册
     * @param dto
     * @return
     */
    @RequestMapping(value = "/register", method = RequestMethod.POST)
    public ApiResult<Map<String, Object>> register(@Valid @RequestBody RegisterDTO dto) {
        User user = iUserService.executeRegister(dto);
        if (ObjectUtils.isEmpty(user)) {
            return ApiResult.failed("账号注册失败,号码已存在");
        }
        Map<String, Object> map = new HashMap<>(16);
        map.put("user", user);
        return ApiResult.success(map,"注册成功");
    }

    /**
     * 登录
     * @param dto
     * @return
     */
    @RequestMapping(value = "/login", method = RequestMethod.POST)
    public ApiResult<Map<String, String>> login(@Valid @RequestBody LoginDTO dto) {
        String token = iUserService.executeLogin(dto);
        if (ObjectUtils.isEmpty(token)) {
            return ApiResult.failed("账号密码错误");
        }
        Map<String, String> map = new HashMap<>(16);
        map.put("token", token);
        return ApiResult.success(map, "登录成功");
    }

    /**
     * 改密
     * @param dto
     * @return
     */
    @RequestMapping(value = "/forget", method = RequestMethod.POST)
    public ApiResult<Map<String, String>> changePass(@Valid @RequestBody LoginDTO dto) {
        String token = iUserService.changePassword(dto);
        Map<String, String> map = new HashMap<>(16);
        if (token == "该号码未注册") {
            return ApiResult.failed(token);
        }
            return ApiResult.success(map,token);
    }

    /**
     * 从token里面获取用户名，在通过用户名获取用户信息
     * @param userName
     * @return
     */
    @RequestMapping(value = "/info", method = RequestMethod.GET)
    public ApiResult<User> getUserByToken(@RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        User user = iUserService.getUserByUsername(userName);
        return ApiResult.success(user);
    }

    /**
     * 通过用户名获取用户信息
     * @param userName
     * @return
     */
    @RequestMapping(value = "/getuser", method = RequestMethod.GET)
    public ApiResult<User> getUser(@RequestParam("username") String userName) {
        User user = iUserService.getUserByUsername(userName);
        if (ObjectUtils.isEmpty(user)){
            return ApiResult.failed("该用户不存在");
        }
        return ApiResult.success(user);
    }

    /**
     * 修改用户名和头像
     * @param newAlias
     * @param newAvatar
     * @param userName
     * @return
     */
    @RequestMapping(value = "/info/change",method = RequestMethod.PUT)
    public ApiResult<User> changeInfo(@RequestParam("alias") String newAlias, @RequestParam("avatar") String newAvatar,@RequestHeader(value = JwtUtil.USER_NAME) String userName){
        boolean isTrue = iUserService.changeAliasAndAvatar(userName,newAvatar,newAlias);
        if (!isTrue)
            return ApiResult.failed("用户名已存在");
        User user = iUserService.getUserByUsername(userName);
        return ApiResult.success(user,"修改成功");
    }

    /**
     * 发送短信验证码
     * @param desMobile
     * @return
     */
    @RequestMapping(value = "/valicode", method = RequestMethod.GET)
    public ApiResult<Map<String,String>> getValiCode(@RequestParam("mobile") String desMobile ) {
        String random = SendMessageUtils.getRandomCode(6);
        //SendMessageUtils.send("SMS账户","接口秘钥","目标号码","发送内容");
        Integer resultCode = SendMessageUtils.send("yesiyuan","d41d8cd98f00b204e980",desMobile,"验证码:"+ random);
        String message = SendMessageUtils.getMessage(resultCode);
        Map<String,String> map = new HashMap<>(16) ;
        map.put("valicode",random) ;
        if (resultCode > 0)
            return ApiResult.success(map,message);
        return ApiResult.failed(message);
    }

    /**
     * 添加收获地址
     * @param delAddress
     * @param userName
     * @return
     */
    @RequestMapping(value = "/add_address", method = RequestMethod.POST)
    public ApiResult<List<Object>> addAddress(@Valid @RequestBody DelAddress delAddress , @RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        User user = iUserService.getUserByUsername(userName);
        delAddress.setUserId(user.getId());
        DelAddress addDelAddress = iDelAddressService.executeAdd(delAddress);
        List<Object> list = new ArrayList<>();
        list.add(addDelAddress);
        return ApiResult.success(list,"新增地址成功");
    }

    /**
     * 获取当前用户全部地址
     * @param userName
     * @return
     */
    @RequestMapping(value = "/address_list", method = RequestMethod.GET)
    public ApiResult<List<DelAddress>> getAddressOfUser(@RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        List<DelAddress> list = iDelAddressService.getAllAddressOfUser(userName);
        return ApiResult.success(list);
    }

    /**
     * 充值
     * @param amount
     * @param userName
     * @return
     */
    @RequestMapping(value = "/recharge", method = RequestMethod.PUT)
    public ApiResult<Integer> Recharge(@RequestParam String amount , @RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        Integer balance = iUserService.executeRecharge(amount,userName) ;
        return ApiResult.success(balance,"充值成功");
    }
}
