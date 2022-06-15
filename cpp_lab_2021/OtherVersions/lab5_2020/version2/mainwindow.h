#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mapwidget.h"
//#include <QToolButton>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QVector>
#include <QMouseEvent>
#include <QDialog>
#include <QPixmap>
#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QHBoxLayout>

class QMyLabel;
class ComboBox : public QComboBox
{
    friend class MainWindow;
    Q_OBJECT
public:
    explicit ComboBox(QWidget* parent = nullptr);

protected:

    void keyReleaseEvent(QKeyEvent *e);
signals:
    void keyEnterReleased();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createToolBar(); //创建顶层工具栏
    void createAction(); //将ui和数据绑定
    void setStart(int X, int Y); //线段起点
    void setEnd(int X, int Y); //线段终点
    void setNextPos (int index); //dj前置结点
    void initScene(); //初始化背景
public slots:
    //void showfloatwindow();
    //void hidefloatwindow();
    void setStartStation(); //传输起始信号
    void setEndStation(); //传输终点信号
    void FindPath(); //dj
    void Clear(); //清屏
    void callOtherMap(); //放大
    void ShowDialog(); //展示路径
    void addStartComboBox(); //输入起点框
    void addEndComboBox(); //输入终止框
    double similarity(const QString& s, const QVector<QString>&t); //返回字符串相似度
    QVector<int>similarest(const QString& s, const QVector<QVector<QString>>v); //返回匹配字符串数组
private:
    MapWidget *mapWidget; //宽度
    QLabel *startLabel; //开始小红点
    QLabel *endLabel; //终点小红点
    QComboBox *reviseComboBox; //

    QAction *findPathAction; //搜索路径按钮
    QAction *clearAction; //清屏按钮
    QAction *callMap; //放大
    QGraphicsScene *scene;//背景
    QGraphicsView *view;//

    int startX, startY, endX, endY;//开始xy，终点xy
    QVector<int> nextPath; //dj数组

    /*
     * 图的实现，和最短路径算法声明
     */
    struct ArcCell{    //弧信息
        int adj;       //对无权图有1，0表示是否相邻，对带权图，则为权值类型
    };


    //内部类
    static const int MAX_VERTEX_NUM = 50;
    static const int INF = 999999;

    struct MGraph{
        QVector<int> vexs;                                    //顶点集合
        //临接矩阵
        ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
        int vexnum;                                           //顶点数
        int arcnum;                                           //边数
    };

    class DijkstraFindPath
    {
    public:
        DijkstraFindPath();
        MGraph mgraph;
        void CreateGraph();

        int prev[MAX_VERTEX_NUM];  //最短路上的前驱顶点
        int d[MAX_VERTEX_NUM];     //表示边e = (u,v)的权值(不存在时为INF,不过d[i][i]=0)
        bool used[MAX_VERTEX_NUM]; //已经使用过的图
        void dijkstra(int startPos);      //求从起点startPos出发到各个顶点的最短距离
        QVector<int> get_Path(int endPos);//到顶点endPos的最短路
        QVector<QVector<int>>Location; //坐标
        QVector<QVector<QString>>names; //名字
    };

    ComboBox *startComboBox;
    ComboBox *endComboBox;
    DijkstraFindPath *dj;

//鼠标事件
protected:
    void mousePressEvent (QMouseEvent *e);
private:
    QPixmap library;
    QPixmap canteen;
    QPixmap jxjBuilding;
    QPixmap westgate;
    QPixmap westground;
    QPixmap twoMarket;
    QString strPath;
    QLabel *label;
    QGraphicsSimpleTextItem *l;
    QGraphicsSimpleTextItem *r;
    int lv=-1;
    int rv=-1;
};


#endif // MAINWINDOW_H
















