package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.milkorder_backend.model.dto.DrinkAddDTO;
import com.example.milkorder_backend.model.entity.Cla;
import com.example.milkorder_backend.model.entity.DrinkImage;

import java.util.List;

public interface IDrinkImageService extends IService<DrinkImage> {

    /**
     * 添加图片
     * @param dto
     * @return
     */
    void executeAdd(DrinkAddDTO dto);

    /**
     * 返回一个奶茶的全部图片
     * @param drinkName
     * @return
     */
    List<String> getAllImages(String drinkName);

}
