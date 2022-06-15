package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.mapper.ClaMapper;
import com.example.milkorder_backend.mapper.DelAddressMapper;
import com.example.milkorder_backend.model.entity.Cla;
import com.example.milkorder_backend.model.entity.DelAddress;
import com.example.milkorder_backend.model.entity.User;
import com.example.milkorder_backend.service.IClaService;
import com.example.milkorder_backend.service.IDelAddressService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.Date;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class IDelAddressServiceImpl extends ServiceImpl<DelAddressMapper, DelAddress> implements IDelAddressService {
    @Resource
    private IUserServiceImpl iUserService;

    // 新增收获地址
    @Override
    public DelAddress executeAdd(DelAddress delAddress) {
        delAddress.setCreateTime(new Date());
        baseMapper.insert(delAddress);
        return delAddress;
    }

    // 获取用户的全部地址
    @Override
    public List<DelAddress> getAllAddressOfUser(String userName) {
        User user = iUserService.getUserByUsername(userName);
        List<DelAddress> list = baseMapper.getAllAddress(user.getId());
        return list;
    }

    // 删除地址
    @Override
    public void executeDelete(String id) {
        baseMapper.deleteById(id) ;
    }

    @Override
    public DelAddress executeUpdate(DelAddress delAddress, String id) {
        String linkman = delAddress.getLinkman();
        boolean isMale = delAddress.getIsMale();
        String mobile = delAddress.getMobile();
        String address = delAddress.getAddress();
        String detail = delAddress.getDetail();
        baseMapper.updateAddress(linkman,isMale,mobile,address,detail,id) ;
        DelAddress newDelAddress = baseMapper.selectById(id);
        return newDelAddress;
    }
}
