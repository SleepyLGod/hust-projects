package com.example.milkorder_backend.threads;

import lombok.extern.slf4j.Slf4j;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.ObjectUtils;

import javax.annotation.Resource;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

@Slf4j  // 日志
@Service  // 标记当前类是一个service类，加上该注解会将当前类自动注入到spring容器中，不需要再在applicationContext.xml文件定义bean了
@Transactional(rollbackFor = Exception.class)
public class OrderFinishThread implements Runnable{

    static String driver = "com.mysql.cj.jdbc.Driver";
    static String url="jdbc:mysql://localhost:3306/milkorder?useUnicode=true&characterEncoding=utf8&autoReconnect=true&serverTimezone=GMT%2B8";
    static String user="root";
    static String pwd = "123456";

    @Override
    public void run() {

        Connection conn = null;
        try {
            //1.加载驱动
            Class.forName(driver);
            //2.取得数据库连接
            conn =  DriverManager.getConnection(url, user, pwd);
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        String getAllStore = "select * from store ;" ;
        String updateStr = "UPDATE drink_order SET is_finish = true where id = ";
        String selectStr = "select * from drink_order where is_finish = false " ;

        ResultSet storeSet = null;
        ResultSet orderSet = null;
        PreparedStatement getStorePs = null;
        PreparedStatement selectPs = null;
        PreparedStatement upDatePs = null;

        // 得到所有的店铺id
        List<String> storeList = new ArrayList<>();
        try {
            getStorePs = conn.prepareStatement(getAllStore);
            storeSet = getStorePs.executeQuery();
            while (storeSet.next()){
                storeList.add(storeSet.getString("id")) ;
            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        // 死循环
        while (true){
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // 对于每个店铺而言，查询最早的一条未完成订单（的id），等1分钟后将其标志设为完成
            for (String s : storeList) {
                String finalSelectStr = selectStr + "and store = " + s + " limit 1 ;" ;
                try {
                    selectPs = conn.prepareStatement(finalSelectStr);
                    orderSet = selectPs.executeQuery();
                    while (orderSet.next()){
                        String id = orderSet.getString("id");
                        upDatePs = conn.prepareStatement(updateStr+ id +";");
                        upDatePs.executeUpdate();
                    }
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }

            // 处理完所有店铺，休眠一分钟
            try {
                Thread.sleep(60000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
