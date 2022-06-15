package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.milkorder_backend.model.dto.DrinkAddDTO;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.Tip;

import java.util.List;

public interface ITipService extends IService<Tip> {
    /**
     * 新增小料，只有管理员才有权限
     *
     * @param tip
     * @return 注册对象
     */
    Tip executeAdd(Tip tip);

    /**
     * 获取小料列表
     * @return
     */
    List<Tip> getList();
    /**
     * 获取小料价格
     * @param name
     * @return
     */
    String getTipPrice(String name);
}
