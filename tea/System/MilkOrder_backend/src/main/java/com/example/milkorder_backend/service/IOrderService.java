package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.milkorder_backend.model.dto.OrderDTO;
import com.example.milkorder_backend.model.entity.Order;
import com.example.milkorder_backend.model.vo.DrinkVO;
import com.example.milkorder_backend.model.vo.OrderVO;

import java.util.List;
import java.util.Map;

public interface IOrderService extends IService<Order> {
    /**
     * 发起订单
     * @param dto
     * @param username
     * @return
     */
    Map executeAddOrder(OrderDTO dto, String username) ;

    /**
     * 历史订单
     * @param username
     * @return
     */
    List<OrderVO> orderListOfUser(String username) ;

    /**
     * 获取某一店铺的等待时间
     * @param store
     * @return
     */
    Integer getWaitTimeOfStore(String store);
}
