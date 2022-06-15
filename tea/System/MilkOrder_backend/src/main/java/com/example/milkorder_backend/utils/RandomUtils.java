package com.example.milkorder_backend.utils;

import java.util.Random;

public class RandomUtils {
    /**
     * 随机生成n位验证码
     * @return
     */
    public static String getRandomCode(Integer code){
        Random random = new Random();
        StringBuffer result= new StringBuffer();
        for (int i=0;i<code;i++){
            result.append(random.nextInt(10));
        }
        return result.toString();
    }
}
