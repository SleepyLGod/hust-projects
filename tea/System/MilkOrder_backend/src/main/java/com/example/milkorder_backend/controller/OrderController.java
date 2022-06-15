package com.example.milkorder_backend.controller;

import com.example.milkorder_backend.common.api.ApiResult;
import com.example.milkorder_backend.jwt.JwtUtil;
import com.example.milkorder_backend.model.dto.DrinkAddDTO;
import com.example.milkorder_backend.model.dto.OrderDTO;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.Order;
import com.example.milkorder_backend.model.entity.User;
import com.example.milkorder_backend.model.vo.OrderVO;
import com.example.milkorder_backend.service.IOrderService;
import com.example.milkorder_backend.service.IStoreService;
import com.example.milkorder_backend.service.IUserService;
import org.springframework.util.ObjectUtils;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/order")
public class OrderController {
    @Resource
    private IOrderService iOrderService;
    @Resource
    private IUserService iUserService;
    @Resource
    private IStoreService iStoreService;

    /**
     * 发起订单
     * @param dto
     * @param userName
     * @return
     */
    @RequestMapping(value = "/add", method = RequestMethod.POST)
    public ApiResult<Map<String, Object>> orderAdd(@Valid @RequestBody OrderDTO dto,@RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        if (!iStoreService.isStoreExit(dto.getStore()))
            return ApiResult.failed("店铺不存在");
        Map map = iOrderService.executeAddOrder(dto, userName);
        Map<String, Object> resMap = new HashMap<>(16);
        if (ObjectUtils.isEmpty(map))
            return ApiResult.failed("下单失败");
        resMap.put("waitTime",map.get("numOfLine")) ;
        resMap.put("code",map.get("code")) ;
        resMap.put("order",map.get("order")) ;
        return ApiResult.success(resMap,"下单成功");
    }

    /**
     * 获取当前用户全部历史订单
     * @param userName
     * @return
     */
    @RequestMapping(value = "/list", method = RequestMethod.GET)
    public ApiResult<List<OrderVO>> getOrderListOfUser(@RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        List<OrderVO> list = iOrderService.orderListOfUser(userName);
        return ApiResult.success(list);
    }

    /**
     * 支付
     * @param cost
     * @param userName
     * @return
     */
    @RequestMapping(value = "/pay", method = RequestMethod.PUT)
    public ApiResult<Integer> orderPay(@RequestParam String cost, @RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        Integer balance =  iUserService.executePay(cost,userName);
        if (balance < 0)
            return ApiResult.failed("余额不足，请充值");
        return ApiResult.success(balance,"支付成功");
    }

    /**
     * 提前获取等待时间
     * @param store
     * @return
     */
    @RequestMapping(value = "/wait_time")
    public ApiResult<Map<String,?>> getWaitTime(@RequestParam String store) {
        if (!iStoreService.isStoreExit(store))
            return ApiResult.failed("店铺不存在");
        Map<String,Integer> map = new HashMap<>();
        map.put("waitTime",iOrderService.getWaitTimeOfStore(store));
        return ApiResult.success(map);
    }
}
