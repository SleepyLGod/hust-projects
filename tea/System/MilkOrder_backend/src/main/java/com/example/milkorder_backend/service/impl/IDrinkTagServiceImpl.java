package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.mapper.DrinkTagMapper;
import com.example.milkorder_backend.model.entity.DrinkTag;
import com.example.milkorder_backend.model.entity.Tag;
import com.example.milkorder_backend.service.IDrinkTagSerivce;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class IDrinkTagServiceImpl extends ServiceImpl<DrinkTagMapper, DrinkTag> implements IDrinkTagSerivce {

    @Resource
    private ITagServiceImpl iTagService;

    @Override
    public void addRelation(String drinkId, String tagId) {
        DrinkTag drinkTag = baseMapper.getRelationByTwo(drinkId,tagId);
        if (ObjectUtils.isEmpty(drinkTag)){
            DrinkTag addDrinkTag = DrinkTag.builder()
                    .drinkId(drinkId)
                    .tagId(tagId)
                    .build();
            baseMapper.insert(addDrinkTag);
        }
    }

    @Override
    public List<String> getTagsByDrinkId(String drinkId) {
        List<DrinkTag> tagList = baseMapper.getTagsOfDrink(drinkId);
        List<String> list = new ArrayList<>();
        for (DrinkTag drinkTag : tagList) {
            list.add(iTagService.getTagNameById(drinkTag.getTagId()));
        }
        return list;
    }
}
