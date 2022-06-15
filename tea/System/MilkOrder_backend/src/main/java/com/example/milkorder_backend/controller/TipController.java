package com.example.milkorder_backend.controller;

import com.example.milkorder_backend.common.api.ApiResult;
import com.example.milkorder_backend.jwt.JwtUtil;
import com.example.milkorder_backend.model.dto.DrinkAddDTO;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.model.entity.Tip;
import com.example.milkorder_backend.model.entity.User;
import com.example.milkorder_backend.service.ITipService;
import com.example.milkorder_backend.service.IUserService;
import org.springframework.util.ObjectUtils;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/tip")
public class TipController {
    @Resource
    private ITipService iTipService;
    @Resource
    private IUserService iUserService;

    int counter = 1 ;

    /**
     * 新增小料
     * @param tip
     * @param userName
     * @return
     */
    @RequestMapping(value = "/add", method = RequestMethod.POST)
    public ApiResult<Map<String, Object>> Add(@Valid @RequestBody Tip tip, @RequestHeader(value = JwtUtil.USER_NAME) String userName) {
        //先看登录用户是否有权限
        User user = iUserService.getUserByUsername(userName);
        if (user.getRoleId() != 2){
            return ApiResult.failed("用户无权限");
        }

        Tip tip1 = iTipService.executeAdd(tip);
        if (ObjectUtils.isEmpty(tip1)) {
            return ApiResult.failed("小料新增失败,已存在");
        }
        Map<String, Object> map = new HashMap<>(16);
        map.put("小料", tip1);
        return ApiResult.success(map);
    }

    /**
     * 获取全部小料列表
     * @return
     */
    @RequestMapping(value = "/list")
    public ApiResult<Map<String, Object>> getDrinkList() {
        Map<String, Object> map = new HashMap<>(16);
        List<Tip> list = iTipService.getList();
        map.put("tip",list);
        return ApiResult.success(map);
    }

}
