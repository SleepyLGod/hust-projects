package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.mapper.TagMapper;
import com.example.milkorder_backend.model.dto.DrinkAddDTO;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.DrinkImage;
import com.example.milkorder_backend.model.entity.Tag;
import com.example.milkorder_backend.service.ITagService;
import com.example.milkorder_backend.service.ITipService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import javax.annotation.Resource;
import java.util.Date;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class ITagServiceImpl extends ServiceImpl<TagMapper, Tag> implements ITagService {

    @Resource
    private IDrinkTagServiceImpl iDrinkTagService;
    @Resource
    private IDrinkServiceImpl iDrinkService;

    @Override
    public void executeAdd(DrinkAddDTO dto) {
        List<String> list = dto.getTags();
        Drink drink = iDrinkService.getDrinkByName(dto.getName());
        for (String name : list) {
            Tag tag = baseMapper.getTag(name);
            // 插入tag表单
            if (ObjectUtils.isEmpty(tag)){
                Tag addTag = Tag.builder()
                        .name(name)
                        .createTime(new Date())
                        .build();
                baseMapper.insert(addTag);
            }
            // 新增关联
            iDrinkTagService.addRelation(drink.getId(),baseMapper.getTag(name).getId());

        }
    }

    @Override
    public String getTagNameById(String id) {
        Tag tag = baseMapper.getTagById(id);
        return tag.getName();
    }
}
