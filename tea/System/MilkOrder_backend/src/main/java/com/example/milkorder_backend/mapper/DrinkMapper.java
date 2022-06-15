package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.Cla;
import com.example.milkorder_backend.model.entity.Drink;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * 奶茶
 */

@Repository
public interface DrinkMapper extends BaseMapper<Drink> {
    /**
     * 通过奶茶名获取奶茶
     * @param name
     * @return
     */
    Drink getDrinkByName(String name) ;

    /**
     * 获取所有奶茶
     * @return
     */
    List<Drink> selectAllDrink();

    /**
     * 获取某一分类下的所有奶茶
     * @return
     */
    List<Drink> selectAllDrinkOfCla(String cla);


}
