package com.example.milkorder_backend.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.milkorder_backend.model.entity.Tag;
import org.springframework.stereotype.Repository;

@Repository
public interface TagMapper extends BaseMapper<Tag> {
    /**
     * 获取标签
     * @param name
     * @return
     */
    Tag getTag(String name);

    /**
     * 由标签id查询标签名
     * @param id
     * @return
     */
    Tag getTagById(String id);
}
