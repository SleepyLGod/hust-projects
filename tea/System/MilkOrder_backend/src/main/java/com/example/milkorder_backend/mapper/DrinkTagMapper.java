package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.DrinkTag;
import com.example.milkorder_backend.model.entity.Tag;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * 奶茶-tag 关联表
 */
@Repository
public interface DrinkTagMapper extends BaseMapper<DrinkTag> {
    /**
     * 查询是否有关联
     * @param drinkId
     * @param tagId
     * @return
     */
    DrinkTag getRelationByTwo(String drinkId,String tagId);

    /**
     * 获取指定奶茶的全部tag
     * @param drinkId
     * @return
     */
    List<DrinkTag> getTagsOfDrink(String drinkId);
}
