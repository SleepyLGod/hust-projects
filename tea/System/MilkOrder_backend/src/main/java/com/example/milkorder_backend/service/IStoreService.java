package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.milkorder_backend.model.entity.Order;
import com.example.milkorder_backend.model.entity.Store;

import java.util.List;

public interface IStoreService extends IService<Store> {
    /**
     * 新增门店
     * @param store
     * @return
     */
    Store executeAdd(Store store);

    /**
     * 获取所有门店
     * @return
     */
    List<Store> getStoreList();

    /**
     * 查询店铺id是否存在
     */
    boolean isStoreExit(String id);

    /**
     * 由id查名称
     */
    String getStoreNameById(String id);
}
