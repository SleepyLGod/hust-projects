package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.Order;
import com.example.milkorder_backend.model.entity.Store;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface OrderMapper extends BaseMapper<Order> {
    /**
     * 返回最早的未完成订单
     * @return
     */
    List<Order> getNoFinishedOrderOfStore(String store);

    /**
     * 获取当前用户全部历史订单
     * @param username
     * @return
     */
    List<Order> getOrderListOfUser(String username);

    /**
     * 返回id对应的店铺
     * @param id
     * @return
     */
    Store getStoreById(String id);
}
