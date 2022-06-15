package com.example.milkorder_backend.controller;

import com.example.milkorder_backend.common.api.ApiResult;
import com.example.milkorder_backend.jwt.JwtUtil;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.Store;
import com.example.milkorder_backend.model.entity.User;
import com.example.milkorder_backend.model.vo.DrinkVO;
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
@RequestMapping("/store")
public class StoreController {
    @Resource
    private IStoreService iStoreService;
    @Resource
    private IUserService iUserService;

    /**
     * 新增门店
     * @param store
     * @param userName
     * @return
     */
    @RequestMapping(value = "/add", method = RequestMethod.POST)
    public ApiResult<Map<String, Object>> Add(@Valid @RequestBody Store store, @RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        //先看登录用户是否有权限
        User user = iUserService.getUserByUsername(userName);
        if (user.getRoleId() != 2){
            return ApiResult.failed("用户无权限");
        }

        Store store1 = iStoreService.executeAdd(store);
        if (ObjectUtils.isEmpty(store1)) {
            return ApiResult.failed("门店新增失败,点名已存在");
        }
        Map<String, Object> map = new HashMap<>(16);
        map.put("store", store1);
        return ApiResult.success(map);
    }

    /**
     * 获取全部门店
     * @return
     */
    @RequestMapping(value = "/list")
    public ApiResult<Map<String, Object>> getDrinkList() {
        int counter = 1;
        Map<String, Object> map = new HashMap<>(16);
        List<Store> list = iStoreService.getStoreList();
        map.put("store",list);
        return ApiResult.success(map);
    }
}
