package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.mapper.StoreMapper;
import com.example.milkorder_backend.mapper.TagMapper;
import com.example.milkorder_backend.model.entity.Store;
import com.example.milkorder_backend.model.entity.Tag;
import com.example.milkorder_backend.service.IStoreService;
import com.example.milkorder_backend.service.ITagService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import java.util.Date;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class IStoreServiceImpl extends ServiceImpl<StoreMapper, Store> implements IStoreService {
    // 新增门店
    @Override
    public Store executeAdd(Store store) {
        Store store1 = baseMapper.getStore(store.getName());
        if (ObjectUtils.isEmpty(store1)){
            Store addStore = Store.builder()
                    .name(store.getName())
                    .address(store.getAddress())
                    .createTime(new Date())
                    .build() ;
            baseMapper.insert(addStore);
            return addStore;
        }
            return null;
    }

    // 获取所有门店
    @Override
    public List<Store> getStoreList() {
        return baseMapper.getStoreList();
    }

    // 查询店铺是否存在
    @Override
    public boolean isStoreExit(String id) {
        Store store = baseMapper.getStoreById(id);
        if (ObjectUtils.isEmpty(store))
            return  false;
        return true;
    }

    // 由id查名称
    @Override
    public String getStoreNameById(String id) {
        Store store = baseMapper.getStoreById(id);
        if (ObjectUtils.isEmpty(store))
            return null;
        return store.getName();
    }
}
