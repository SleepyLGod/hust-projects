package com.example.milkorder_backend.controller;

import com.example.milkorder_backend.common.api.ApiResult;
import com.example.milkorder_backend.model.entity.Cla;
import com.example.milkorder_backend.model.entity.Drink;
import com.example.milkorder_backend.service.IClaService;
import com.example.milkorder_backend.service.IDrinkService;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/cla")
public class ClaController {
    @Resource
    private IClaService iClaService;

    int counter = 1;

    @RequestMapping(value = "/list")
    public ApiResult<Map<String, Object>> getClaList() {
        Map<String, Object> map = new HashMap<>(16);
        List<Cla> list = iClaService.getClaList();
        map.put("class",list);
        return ApiResult.success(map);
    }

}
