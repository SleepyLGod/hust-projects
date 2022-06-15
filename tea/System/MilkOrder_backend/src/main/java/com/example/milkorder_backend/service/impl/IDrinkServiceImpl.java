package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.common.exception.ApiAsserts;
import com.example.milkorder_backend.mapper.DrinkMapper;
import com.example.milkorder_backend.mapper.UserMapper;
import com.example.milkorder_backend.model.dto.DrinkAddDTO;
import com.example.milkorder_backend.model.dto.RegisterDTO;
import com.example.milkorder_backend.model.entity.Cla;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.Tag;
import com.example.milkorder_backend.model.entity.User;
import com.example.milkorder_backend.service.IClaService;
import com.example.milkorder_backend.service.IDrinkService;
import com.example.milkorder_backend.service.IUserService;
import com.example.milkorder_backend.utils.MD5Utils;
import lombok.extern.slf4j.Slf4j;
import org.junit.Test;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import javax.annotation.Resource;
import java.util.Date;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class IDrinkServiceImpl extends ServiceImpl<DrinkMapper,Drink> implements IDrinkService {
    @Resource
    private IClaService iClaService;
    @Resource
    private IDrinkImageServiceImpl iDrinkImageService;
    @Resource
    private ITagServiceImpl iTagService;

    // 1. 新增奶茶
    @Override
    public Drink executeAdd(DrinkAddDTO dto) {

        // 查询是否有相同名称的奶茶
        Drink drink = baseMapper.getDrinkByName(dto.getName());
        if (!ObjectUtils.isEmpty(drink)) {
            // 匹配成功说明已存在
            return null;
        }
        // 否者，创建一个新增对象addDrink依次设置字段值，然后插入表单
        Drink addDrink = Drink.builder()
                .name(dto.getName())
                .price(dto.getPrice())
                .cla(dto.getCla())
                .des(dto.getDescribe())
                .createTime(new Date())
                .build();
        this.baseMapper.insert(addDrink);

        // 添加新的分类
        iClaService.addCla(addDrink.getCla());

        // 添加图片
        iDrinkImageService.executeAdd(dto);

        // 添加Tag以及对应关联
        iTagService.executeAdd(dto);

        return addDrink;
    }

    // 2. 获取奶茶列表
    @Override
    public List<Drink> getDrinkList() {
        return this.baseMapper.selectAllDrink();
    }

    // 3. 获取某一分类下的奶茶列表
    @Override
    public List<Drink> getListByCla(String cla) {
        return this.baseMapper.selectAllDrinkOfCla(cla);
    }

    // 4. 用奶茶名获取奶茶
    @Override
    public Drink getDrinkByName(String name) {
        return this.baseMapper.getDrinkByName(name);
    }
}
