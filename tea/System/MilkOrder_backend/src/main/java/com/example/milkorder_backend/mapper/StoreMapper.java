package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.Store;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface StoreMapper extends BaseMapper<Store> {
    /**
     * 查询店铺是否存在
     * @param name
     * @return
     */
    Store getStore(String name);

    /**
     * 获取所有门店
     * @return
     */
    List<Store> getStoreList();

    /**
     * 通过id查店铺
     * @param id
     * @return
     */
    Store getStoreById(String id);
}
