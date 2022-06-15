package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.DrinkImage;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * 奶茶图片
 */
@Repository
public interface DrinkImageMapper extends BaseMapper<DrinkImage>  {

    /**
     * 获取图片信息
     * @param url
     * @return
     */
    DrinkImage getImage(String url);

    /**
     * 返回对应奶茶的所有图片地址
     * @param drinkName
     * @return
     */
    List<DrinkImage> getAllImages(String drinkName) ;
}
