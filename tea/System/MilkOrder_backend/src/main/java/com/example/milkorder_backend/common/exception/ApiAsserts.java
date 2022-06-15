package com.example.milkorder_backend.common.exception;

import com.baomidou.mybatisplus.extension.exceptions.ApiException;
import com.example.milkorder_backend.common.api.IErrorCode;

public class ApiAsserts {
    /**
     * 抛失败异常
     *
     * @param message 说明
     */
    public static void fail(String message) {
        throw new ApiException(message);
    }

    /**
     * 抛失败异常
     *
     * @param errorCode 状态码
     */
    public static void fail(IErrorCode errorCode) {
        throw new ApiException((com.baomidou.mybatisplus.extension.api.IErrorCode) errorCode);
    }
}
