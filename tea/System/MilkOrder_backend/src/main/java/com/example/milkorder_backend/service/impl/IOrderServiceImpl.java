package com.example.milkorder_backend.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.milkorder_backend.mapper.OrderMapper;
import com.example.milkorder_backend.mapper.TipMapper;
import com.example.milkorder_backend.model.dto.OneOrderDTO;
import com.example.milkorder_backend.model.dto.OrderDTO;
import com.example.milkorder_backend.model.entity.*;
import com.example.milkorder_backend.model.vo.DrinkVO;
import com.example.milkorder_backend.model.vo.OrderVO;
import com.example.milkorder_backend.service.*;
import com.example.milkorder_backend.utils.RandomUtils;
import lombok.extern.slf4j.Slf4j;
import org.junit.Test;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import javax.annotation.Resource;
import java.text.SimpleDateFormat;
import java.time.Year;
import java.util.*;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class IOrderServiceImpl extends ServiceImpl<OrderMapper, Order> implements IOrderService {

    @Resource
    private IUserService iUserService;
    @Resource
    private IDrinkService iDrinkService;
    @Resource
    private ITipService iTipService;
    @Resource
    private IDrinkImageServiceImpl iDrinkImageService;
    @Resource
    private  IStoreService iStoreService;

    // 1. 发起订单
    @Override
    public Map<String,?> executeAddOrder(OrderDTO dto, String username) {

        List<OneOrderDTO> list = dto.getProducts();
        List<Order> orderList = new ArrayList<>();
        Map map = new HashMap<>();
        int counter = 1;
        String code = RandomUtils.getRandomCode(4) ; // 随机四位取件码
        String drinkName = "" ;
        String allTipDes = "";
        String allOtherDes = "";
        Double cost = 0.0 ;
        String number = "";

        for (OneOrderDTO oneOrderDTO : list) {
            Drink drink = iDrinkService.getDrinkByName(oneOrderDTO.getDrinkName());
            // 杯数
            number = number + oneOrderDTO.getDrinkNum() + "+" ;
            // 计算奶茶价格
            cost += Double.parseDouble(drink.getPrice()) * oneOrderDTO.getDrinkNum();
            if (ObjectUtils.isEmpty(drink)){
                return null;
            }
            drinkName = drinkName + oneOrderDTO.getDrinkName() + "\t";
            allOtherDes = allOtherDes + oneOrderDTO.getOtherDes() + "\t";
            allTipDes = allTipDes + oneOrderDTO.getTipDes() + "\t";
            // 计算所有小料总价格
            String tipDes = oneOrderDTO.getTipDes();
            for (int i = -1 ; i < tipDes.length() ; i = tipDes.indexOf("&",i) + 1){
                if (i == 0 )
                    break;
                else if (i == -1)
                    i++;
                if (tipDes.indexOf("&",i) != -1)
                    cost += Double.parseDouble(iTipService.getTipPrice(tipDes.substring(i,tipDes.indexOf("&",i)))) ;
                else
                    cost += Double.parseDouble(iTipService.getTipPrice(tipDes.substring(i,tipDes.length())));
            }

        }

            // 插入表单
            Order addOrder = Order.builder()
                    .delId(dto.getDelId())
                    .username(username)
                    .store(dto.getStore())
                    .createTime(new Date())
                    .isTakeOut(dto.isTakeOut())
                    .drinkName(drinkName)
                    .drinkNum(number)
                    .price(String.valueOf(cost))
                    .tipDes(allTipDes)
                    .otherDes(allOtherDes)
                    .code(code)
                    .build();
            baseMapper.insert(addOrder) ;
            addOrder.setStore(iStoreService.getStoreNameById(dto.getStore()));
            orderList.add(addOrder);

        map.put("order",orderList);

        // 计算排队时间
        List<Order> noFinishedOrder = baseMapper.getNoFinishedOrderOfStore(dto.getStore());
        if (ObjectUtils.isEmpty(noFinishedOrder)){
            map.put("numOfLine",0);
        }
        else
            map.put("numOfLine",noFinishedOrder.size());

        map.put("code",code);

        return map;
    }

    // 全部历史订单
    @Override
    public List<OrderVO> orderListOfUser(String username) {
        List<Order> list =  baseMapper.getOrderListOfUser(username) ;
        List<OrderVO> orderVOList = new ArrayList<>();

        for (Order order : list) {
            Integer counter = 0;
            Integer number = 0;
            String allDrinkName = order.getDrinkName();
            // 获取每一种奶茶的杯数
            List<String> num = new ArrayList<>();
            String allNum = order.getDrinkNum();
            for (int i = -1 ; i < allNum.length() ; i = allNum.indexOf("+",i) + 1){
                if (i == 0 )
                    break;
                else if (i == -1)
                    i++;
                if (allNum.indexOf("+",i) != -1){
                    num.add(allNum.substring(i,allNum.indexOf("+",i)));
                }

            }


            List<DrinkVO> drinks = new ArrayList<>();
            // 获取某一订单下的所有奶茶
            for (int i = -1 ; i < allDrinkName.length() ; i = allDrinkName.indexOf("\t",i) + 1){
                if (i == 0 )
                    break;
                else if (i == -1)
                    i++;
                if (allDrinkName.indexOf("\t",i) != -1){
                    Drink drink = iDrinkService.getDrinkByName(allDrinkName.substring(i,allDrinkName.indexOf("\t",i)));
                    DrinkVO drinkVO = DrinkVO.builder()
                            .name(drink.getName())
                            .images(iDrinkImageService.getAllImages(drink.getName()))
                            .price(drink.getPrice())
                            .num(Integer.parseInt(num.get(counter)))
                            .build();
                    number += Integer.parseInt(num.get(counter)) ;
                    counter++ ;
                    drinks.add(drinkVO);
                }

            }

            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm");  // 格式化时间

            OrderVO orderVO = OrderVO.builder()
                    .delId(order.getDelId())
                    .store(iStoreService.getStoreNameById(order.getStore()))
                    .code(order.getCode())
                    .drinkNum(number)
                    .drink(drinks)
                    .id(order.getId())
                    .isTakeOut(order.getIsTakeOut())
                    .isFinish(order.getIsFinish())
                    .otherDes(order.getOtherDes())
                    .tipDes(order.getTipDes())
                    .price(order.getPrice())
                    .username(order.getUsername())
                    .createTime(sdf.format(order.getCreateTime()))
                    .build();

            orderVOList.add(orderVO);
        }

        return orderVOList;
    }

    @Override
    public Integer getWaitTimeOfStore(String store) {
        // 计算排队时间
        List<Order> noFinishedOrder = baseMapper.getNoFinishedOrderOfStore(store);
        if (ObjectUtils.isEmpty(noFinishedOrder)){
            return 1;
        }
        else
           return noFinishedOrder.size();
    }
}
