#ifndef CLIMBOTWIN_H
#define CLIMBOTWIN_H

#include <QMainWindow>
// #include "fish_show_finsih/fish.h"
#include <QWidget>
#include <QtCharts>             // 必须这么设置
#include <QtDataVisualization>  // 绘图
#include <QTimer>               // 定时器
#include <QTcpSocket>           // 通信套接字
#include <QFile>                // 读取文本
#include <QTextStream>
#include <QKeyEvent>
#include <QScreen>
#include <Qt3DInput/QInputAspect>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include "dobotmodel.h"
#include "panel.h"
#include "dataview.h"
#include "connectrobot.h"
#include "lineentity.h"
#include "axesentity.h"
#include "auxiliatyentity.h"
#include "axesentity_robot.h"
#include "trajectory.h"
#include <QVector>

/*
// 3D三点图的绘图：
using QtDataVisualization::Q3DScatter;          // 渲染3D散点图的方法
using QtDataVisualization::QScatter3DSeries;    // 表示3D散点图中的数据系列
using QtDataVisualization::QScatterDataProxy;   // 3D散点图的数据代理
using QtDataVisualization::QAbstract3DSeries;   // 所有数据系列的基类
using QtDataVisualization::QAbstract3DGraph;    // 图形的窗口和渲染循环
using QtDataVisualization::Q3DCamera;           // 3D空间中相机的表示
using QtDataVisualization::QScatterDataArray;   // 用项目项目替换位置索引处的项目
using QtDataVisualization::Q3DTheme;            // 图形的视觉样式
*/

namespace Ui {
class ClimbotWin;
}

class ClimbotWin : public QMainWindow {
    Q_OBJECT

public:
    explicit ClimbotWin(QWidget *parent = nullptr);
    ~ClimbotWin();
    void UpdateInfo(QString Type,QString data);
    void BeauCli();
    void Panelinit();
    void DataviewInit();
    void ButtonEnable();
    void ButtonDisable();
    DobotModel *dobotModel;
    void loadDobotModel();

private:
   QWidget     *graphContainer;
   Q3DScatter  *graph3D;           // 散点图
   QScatter3DSeries *series_3D;    // 散点序列
   /*
   // 初始化绘图
   void  iniScatterChart();
   void  iniGraph3D();
   */

private slots:
   // 功能按钮
    void on_ConnectBtn_clicked();

    void on_StartBtn_clicked();

    void on_FinishBtn_clicked();

    void on_OpenFileBtn_clicked();

    void on_EngineStartBtn_clicked();

    void on_EngineStopBtn_clicked();

    void on_cwBtn_clicked();

    void on_ccwBtn_clicked();

    void UpdateFanData();


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    /*
    // panel
    void UpdateData1();
    void UpdateData2();
    void UpdateData3();
    */

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::ClimbotWin *ui;
    ConnectRobot* ConRbt;
    // panel
    panel *panel1;
    panel *panel2;
    panel *panel3;

    QTimer *updateTimer1;
    QTimer *updateTimer2;
    QTimer *updateTimer3;
    // dataview
    QTimer* timer_t;

    qreal A;
    qreal B;
    qreal C;
    qreal D;
    qreal G;

    qreal H;
    qreal I;
    qreal J;
    qreal R;
    qreal T;

    qreal m_M;
    qreal m_S;
    qreal m_E;

    float M;
    float S;
    float E;
    double F;
    double r;
    double t;

    QScatterSeries *series0;
    QScatterSeries *series1;
    QScatterSeries *series2;

    QSplineSeries *seriesLine;
    QSplineSeries *seriesLine1;
    QSplineSeries *seriesLine2;

    QValueAxis *axisX ;
    QValueAxis *axisX1 ;
    QValueAxis *axisX2 ;

    QValueAxis *axisY;
    QValueAxis *axisY1;
    QValueAxis *axisY2;

    // 是否键盘控制
    bool control;

    // 坐标
    float robot_x=0;
    float robot_y=0;
    float robot_z=0;

    // 欧拉角
    float angle1=0;
    float angle2=0;
    float angle3=0;

    // 四元数
    float quanternion_W = 0;
    float quanternion_X = 0;
    float quanternion_Y = 0;
    float quanternion_Z = 0;

    // 轨迹线实体
    Trajectory *trajectory;
    // 判断是否有无轨迹
    bool isTrajectory = false;
    // 显示计数器
    int count_trajectory = 0;
    // 轨迹计时
    QTimer *timer;

    // 测试
    QTimer *tim;

private:
    QTcpSocket *tcpSocket;      // tcp通信套接字
    int fan_1, fan_2, fan_3;    // 风腔负压值
    double ang_vel;             // 旋转角速度
    double distance;
    QFile *file;

protected:
    void keyPressEvent(QKeyEvent *ev);

public slots:
    /*
    // 测试
    void timerUpDate();
    void timerEvent(QTimerEvent *t);
    void onTimeOut();
    */
};

#endif // MAINWINDOW_H
