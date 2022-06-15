package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.milkorder_backend.model.entity.DrinkTag;
import com.example.milkorder_backend.model.entity.Tag;

import java.util.List;

public interface IDrinkTagSerivce extends IService<DrinkTag> {
    /**
     * 新增关联
     * @param drinkId
     * @param tagId
     */
    void addRelation(String drinkId,String tagId);

    /**
     * 获取某一奶茶的全部tag
     * @param drinkId
     * @return
     */
    List<String> getTagsByDrinkId(String drinkId);
}
