package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.milkorder_backend.model.entity.Cla;

import java.util.List;

public interface IClaService extends IService<Cla> {
    /**
     * 获取全部分类
     * @return
     */
    List<Cla> getClaList() ;

    /**
     * 新增分类
     * @param cla
     * @return
     */
    void addCla(String cla);
}
