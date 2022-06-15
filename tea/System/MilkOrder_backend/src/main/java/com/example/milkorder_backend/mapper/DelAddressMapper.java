package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.DelAddress;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface DelAddressMapper extends BaseMapper<DelAddress> {
    /**
     * 获取用户全部地址
     * @param userId
     * @return
     */
    List<DelAddress> getAllAddress(String userId);

    /**
     * 更新地址
     * @param linkman
     * @param isMale
     * @param mobile
     * @param address
     * @param detail
     * @param id
     * @return
     */
    void updateAddress(String linkman, boolean isMale, String mobile ,String address ,String detail, String id);
}
