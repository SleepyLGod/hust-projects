package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.mapper.DrinkImageMapper;
import com.example.milkorder_backend.mapper.DrinkMapper;
import com.example.milkorder_backend.model.dto.DrinkAddDTO;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.DrinkImage;
import com.example.milkorder_backend.service.IDrinkImageService;
import com.example.milkorder_backend.service.IDrinkService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class IDrinkImageServiceImpl extends ServiceImpl<DrinkImageMapper, DrinkImage> implements IDrinkImageService {
    @Override
    public void executeAdd(DrinkAddDTO dto) {
        List<String> list = dto.getImages();
        for (String url : list) {
            DrinkImage image = baseMapper.getImage(url);
            if (ObjectUtils.isEmpty(image)){
                DrinkImage addImage = DrinkImage.builder()
                        .url(url)
                        .drinkName(dto.getName())
                        .createTime(new Date())
                        .build();
                baseMapper.insert(addImage);
            }
        }
    }

    @Override
    public List<String> getAllImages(String drinkName) {
        List<DrinkImage> list = baseMapper.getAllImages(drinkName);
        List<String> urlList = new ArrayList<>();
        for (DrinkImage image : list) {
            urlList.add(image.getUrl());
        }
        return urlList;
    }
}
