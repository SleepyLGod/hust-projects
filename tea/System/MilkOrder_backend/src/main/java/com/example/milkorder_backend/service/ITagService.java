package com.example.milkorder_backend.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.example.milkorder_backend.model.dto.DrinkAddDTO;
import com.example.milkorder_backend.model.entity.Tag;

public interface ITagService extends IService<Tag> {
    /**
     * 插入标签
     * @param dto
     */
    void executeAdd(DrinkAddDTO dto);

    /**
     * 由标签id返回标签名
     * @param id
     * @return
     */
    String getTagNameById(String id);
}
