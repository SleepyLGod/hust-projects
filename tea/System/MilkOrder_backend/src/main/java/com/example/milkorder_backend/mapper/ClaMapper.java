package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.Cla;
import com.example.milkorder_backend.model.entity.User;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface ClaMapper extends BaseMapper<Cla> {
    /**
     * 获取所有分类
     * @return
     */
    List<Cla> getClaList();

    /**
     * 由分类名查询分类
     * @param cla
     * @return
     */
    Cla getClaByName(String cla);

}
