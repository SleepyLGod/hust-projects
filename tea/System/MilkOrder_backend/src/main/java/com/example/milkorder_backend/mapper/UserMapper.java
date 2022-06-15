package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.User;
import org.springframework.stereotype.Repository;

/**
 * 用户
 */

@Repository
public interface UserMapper extends BaseMapper<User> {


    /**
     * 更新余额
     * @param balance
     * @param id
     */
    void updateBalance(Integer balance,String id);

}
