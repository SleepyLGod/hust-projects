#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts>  //必须这么设置
#include <QtDataVisualization>
#include <QTimer>


//using namespace QtDataVisualization;
using QtDataVisualization::Q3DScatter;
using QtDataVisualization::QScatter3DSeries;
using QtDataVisualization::QScatterDataProxy;
using QtDataVisualization::QAbstract3DSeries;
using QtDataVisualization::QAbstract3DGraph;
using QtDataVisualization::Q3DCamera;
using QtDataVisualization::QScatterDataArray;
using QtDataVisualization::Q3DTheme;

//namespace Ui {
//class dataview;
//}

class dataview : public QWidget
{
    Q_OBJECT

private:
    QWidget     *graphContainer;//
    Q3DScatter  *graph3D;       //散点图
    QScatter3DSeries *series;  //散点序列
  //初始化绘图
   void  iniScatterChart();

public:
    explicit dataview(QWidget *parent=nullptr);
    ~dataview();

private slots:
    void  iniGraph3D();


    void buildScatterChart();


private:
//    Ui::dataview *ui;
    QTimer* timer_t;
    qreal M;
    qreal S;
    qreal E;

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

};

#endif // MAINWINDOW_H
