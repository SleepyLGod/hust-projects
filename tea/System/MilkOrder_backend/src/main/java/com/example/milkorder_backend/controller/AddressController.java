package com.example.milkorder_backend.controller;

import com.example.milkorder_backend.common.api.ApiResult;
import com.example.milkorder_backend.jwt.JwtUtil;
import com.example.milkorder_backend.model.entity.DelAddress;
import com.example.milkorder_backend.model.entity.User;
import com.example.milkorder_backend.service.IDelAddressService;
import com.example.milkorder_backend.service.IUserService;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/address")
public class AddressController {

    @Resource
    private IUserService iUserService;
    @Resource
    private IDelAddressService iDelAddressService;
    /**
     * 添加收获地址
     * @param delAddress
     * @param userName
     * @return
     */
    @RequestMapping(value = "/add", method = RequestMethod.POST)
    public ApiResult<DelAddress> addAddress(@Valid @RequestBody DelAddress delAddress , @RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        User user = iUserService.getUserByUsername(userName);
        delAddress.setUserId(user.getId());
        DelAddress addDelAddress = iDelAddressService.executeAdd(delAddress);
        return ApiResult.success(addDelAddress,"新增收获信息成功");
    }

    /**
     * 获取当前用户全部地址
     * @param userName
     * @return
     */
    @RequestMapping(value = "/list", method = RequestMethod.GET)
    public ApiResult<List<DelAddress>> getAddressOfUser(@RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        List<DelAddress> list = iDelAddressService.getAllAddressOfUser(userName);
        return ApiResult.success(list);
    }

    /**
     * 删除接口
     * @param id
     * @return
     */
    @RequestMapping(value = "/delete", method = RequestMethod.DELETE)
    public ApiResult<Object> addAddress(@RequestParam String id) {
        iDelAddressService.executeDelete(id);
        return ApiResult.success();
    }

    /**
     * 更改地址
     * @param delAddress
     * @param id
     * @return
     */
    @RequestMapping(value = "/update", method = RequestMethod.PUT)
    public ApiResult<DelAddress> updateAddress(@Valid @RequestBody DelAddress delAddress , @RequestParam String id) {
        DelAddress newDelAddress = iDelAddressService.executeUpdate(delAddress,id) ;
        return ApiResult.success(newDelAddress,"更改收货信息成功");
    }
}
