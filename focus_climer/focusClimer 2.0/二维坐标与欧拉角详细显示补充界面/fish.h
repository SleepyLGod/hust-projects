#ifndef FISH_H
#define FISH_H

#include <QMainWindow>
#include <QtCharts>  //必须这么设置
#include <QtDataVisualization>
#include <QTimer>
using namespace QtDataVisualization;


namespace Ui {
class fish;
}

class fish : public QMainWindow
{
    Q_OBJECT

private:
    QWidget     *graphContainer;//
    Q3DScatter  *graph3D;       //散点图
    QScatter3DSeries *series;  //散点序列
  //初始化绘图
   void  iniScatterChart();

public:
    explicit fish(QWidget *parent = nullptr);
    ~fish();

private slots:
    void  iniGraph3D();
    void on_chkBoxGrid_clicked(bool checked);

    void on_chkBoxSmooth_clicked(bool checked);

    void on_chkBoxReflection_clicked(bool checked);

    void on_chkBoxAxisTitle_clicked(bool checked);

    void on_chkBoxAxisBackground_clicked(bool checked);

    void on_chkBoxReverse_clicked(bool checked);

    void on_chkBoxBackground_clicked(bool checked);

    void on_spinFontSize_valueChanged(int arg1);

    void on_cBoxTheme_currentIndexChanged(int index);

    void on_btnBarColor_clicked();

    void on_chkBoxItemLabel_clicked(bool checked);

    void on_cBoxBarStyle_currentIndexChanged(int index);

    void on_cBoxSelectionMode_currentIndexChanged(int index);

    void on_spinItemSize_valueChanged(double arg1);

    void on_chkBoxShadow_clicked(bool checked);

    void on_comboBox_currentIndexChanged(int index);

    void on_sliderH_valueChanged(int value);

    void on_sliderV_valueChanged(int value);

    void on_sliderZoom_valueChanged(int value);

   // void timerUpDate_MES();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_chartBarLegendMarkerClicked();

    void on_LegendMarkerClicked();

    void on_chart_2Clicked();

    void buildScatterChart();


private:
    Ui::fish *ui;
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
