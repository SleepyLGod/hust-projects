package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.mapper.ClaMapper;
import com.example.milkorder_backend.mapper.DrinkMapper;
import com.example.milkorder_backend.model.entity.Cla;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.service.IClaService;
import com.example.milkorder_backend.service.IDrinkService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import java.util.Date;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class IClaServiceImpl extends ServiceImpl<ClaMapper, Cla> implements IClaService {

    @Override
    public List<Cla> getClaList() {
        return baseMapper.getClaList();
    }

    @Override
    public void addCla(String cla) {
        // 判断该分类是否已存在
        Cla cla1 = baseMapper.getClaByName(cla);
        if (ObjectUtils.isEmpty(cla1)){
            // 不能存在，则新增
            Cla addCla = Cla.builder()
                    .name(cla)
                    .createTime(new Date())
                    .build();
            baseMapper.insert(addCla);
        }
    }
}
