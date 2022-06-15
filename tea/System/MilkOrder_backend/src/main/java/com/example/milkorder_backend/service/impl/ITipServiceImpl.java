package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.mapper.TipMapper;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.Tip;
import com.example.milkorder_backend.service.ITipService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import java.util.Date;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class ITipServiceImpl extends ServiceImpl<TipMapper, Tip> implements ITipService {
    // 1.新增小料
    @Override
    public Tip executeAdd(Tip tip) {
        // 查询是否有相同名称的奶茶
        Tip tip1 = baseMapper.getTipByName(tip.getName());
        if (!ObjectUtils.isEmpty(tip1)) {
            // 匹配成功说明已存在
            return null;
        }
        // 否者，创建一个新增对象addTip依次设置字段值，然后插入表单
        Tip addTip = Tip.builder()
                .name(tip.getName())
                .price(tip.getPrice())
                .picture(tip.getPicture())
                .createTime(new Date())
                .build();
        baseMapper.insert(addTip);

        return addTip;
    }

    // 2.获取全部小料
    @Override
    public List<Tip> getList() {
        return this.baseMapper.selectAllTip();
    }

    // 3. 获取某一小料价格
    @Override
    public String getTipPrice(String name) {
        if (ObjectUtils.isEmpty(baseMapper.getTipByName(name)))
                return "0" ;  // 小料不存在，价格为0
        return this.baseMapper.getTipByName(name).getPrice();
    }
}
