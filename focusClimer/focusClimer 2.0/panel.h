// 控制面板的设计
#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QPainter>
#include <algorithm>
#include <complex>
#include <QTimer>


class panel : public QWidget {

    Q_OBJECT

public:
    explicit panel(QWidget *parent = nullptr);

    void setTitle(const QString &title);

protected:
    void paintEvent(QPaintEvent *);
    void drawCrown(QPainter *painter);
    void drawScale(QPainter *painter);

    void drawScaleNum(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawIndicator(QPainter *painter);
    void drawNumericalValue(QPainter *painter);
    void drawColorPie(QPainter *painter);
    void drawCoverCircle(QPainter *painter);

private:
    void initVariables();

    QColor m_background;
    QColor m_foreground;

    int m_maxValue;
    int m_minValue;
    int m_startAngle;
    int m_endAngle;

    int m_scaleMajor;               // 表盘分度值
    int m_scaleMinor;

    double m_value;
    int m_precision;
    QTimer *m_updateTimer;
    QTimer* singleTimer;

    QString m_units;
    QString m_title;                // 单位

    QColor pieColorStart;           // 饼圆开始颜色
    QColor pieColorMid;             // 饼圆中间颜色
    QColor pieColorEnd;             // 饼圆结束颜色
    QColor coverCircleColor;        // 饼盘覆盖色

public slots:
    void setValue(qreal value);
/*
      void setAnimating(bool enable)
      {
          m_bAnimating=enable;
          update();
      }

  public:
      bool isAnimating() const
      {
          return m_bAnimating;
      }
*/
public Q_SLOTS:
    void UpdateAngle();             // 转动



};

#endif // PANEL_H
