package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.Tip;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface TipMapper  extends BaseMapper<Tip> {
    /**
     * 通过小料名获取小料
     * @param name
     * @return
     */
    Tip getTipByName(String name) ;

    /**
     * 获取所有小料
     * @return
     */
    List<Tip> selectAllTip();
}
