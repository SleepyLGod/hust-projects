package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.milkorder_backend.model.entity.DelAddress;

import java.util.List;

public interface IDelAddressService extends IService<DelAddress> {
    /**
     * 新增地址
     * @param delAddress
     * @return
     */
    DelAddress executeAdd(DelAddress delAddress);

    /**
     * 获取当前用户的所有
     * @param userName
     * @return
     */
    List<DelAddress> getAllAddressOfUser(String userName);

    /**
     * 删除地址
     * @param id
     */
    void executeDelete(String id);

    /**
     * 更改地址信息
     * @param id
     * @return
     */
    DelAddress executeUpdate(DelAddress delAddress, String id);
}
