// 风腔压力仪表盘的绘制
#include "panel.h"

panel::panel(QWidget * parent): QWidget(parent) {
    initVariables();
}

void panel::initVariables() {
    m_background = Qt::white;
    m_foreground = QColor(0, 19, 150);
    m_startAngle = 45;
    m_endAngle = 45;

    // 三色饼盘
    pieColorStart = QColor(0, 192, 233);
    pieColorMid = QColor(123, 254, 210);
    pieColorEnd = QColor(0, 126, 235);
    coverCircleColor = Qt::white;

    m_minValue = 0;
    m_maxValue = 10;

    // 分度
    m_scaleMajor = 5;
    m_scaleMinor = 10;

    m_units = "KPa";
    m_title = "压力值";
    m_precision = 2;

    m_value = 0;
    m_updateTimer = new QTimer(this);
    m_updateTimer -> setInterval(50); // 间隔，微妙微单位，大家可以改一下这个值看看转动速度。
    m_updateTimer -> start(); // 启动定时器
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(UpdateAngle()));

    setWindowFlags(Qt::FramelessWindowHint); // 无窗体
    setAttribute(Qt::WA_TranslucentBackground); // 背景透明
    resize(200, 200); // 大小
}

void panel::setTitle(const QString & title) {
    m_title = title;
}

void panel::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    /* 使用反锯齿(如果可用) */
    painter.setRenderHint(QPainter::Antialiasing);
    /* 坐标变换为窗体中心  即平移坐标系*/
    painter.translate(width() / 2, height() / 2); // （dx,dy）
    /* 比例缩放 */
    int side = qMin(width(), height());
    painter.scale(side / 220.0, side / 220.0); //  painter.scale(side / 10.0, side / 10.0);
    /* 画表盘边框 */
    drawCrown(& painter);
    /* 画三色盘颜色 */
    drawColorPie(& painter);
    /* 画三色盘覆盖色 */
    drawCoverCircle(& painter);
    /* 画刻度数值值 */
    drawScaleNum(& painter);
    /* 画刻度线 */
    drawScale(& painter);
    /* 画单位 */
    drawTitle(& painter);
    /* 画数字显示 */
    drawNumericalValue(& painter);
    /* 画表针 */
    drawIndicator(& painter);
    painter.end();
}

// 表盘边框
void panel::drawCrown(QPainter * painter) {
    painter -> save();
    int radius = 110;
    painter -> setBrush(QColor(0, 126, 235));
    painter -> setPen(Qt::lightGray); // 边框线无色
    painter -> drawEllipse(-radius, -radius, radius << 1, radius << 1);
    painter -> setBrush(m_background);
    painter -> drawEllipse(-105, -105, 210, 210);
    painter -> restore();
}

// 画刻度线
void panel::drawScale(QPainter * painter) {
    painter -> save();
    painter -> rotate(m_startAngle); // 函数实现角度的旋转
    int steps = (m_scaleMajor * m_scaleMinor); // 相乘后的值是分的份数
    double angleStep = (360.0 - m_startAngle - m_endAngle) / steps; // 每一个份数的角度
    QPen pen;
    pen.setColor(Qt::black);
    for (int i = 0; i <= steps; i++) {
        if (i % m_scaleMinor == 0) { // 整数刻度显示加粗

            pen.setWidth(2); // 设置线宽
            painter -> setPen(pen); // 使用面向对象的思想，把画笔关联上画家。通过画家画出来
            painter -> drawLine(0, 65, 0, 74); // 画线从(x1, y1)到(x2, y2)
        } else {
            pen.setWidth(2);
            painter -> setPen(pen);
            painter -> drawLine(0, 70, 0, 74);
        }
        if (i % 5 == 0) {
            pen.setWidth(1);
            painter -> setPen(pen);
            painter -> drawLine(0, 65, 0, 74);
        }
        painter -> rotate(angleStep);
    }
    painter -> restore();
}

// 刻度数数值
void panel::drawScaleNum(QPainter * painter) {
    painter -> save();
    painter -> setPen(m_foreground);
    // m_startAngle是起始角度，m_endAngle是结束角度， m_scaleMajor在一个量程中分成的刻度数
    double startRad = (270 - m_startAngle) * (3.14 / 180);
    double deltaRad = (360 - m_startAngle - m_endAngle) * (3.14 / 180) / m_scaleMajor;
    double sina, cosa;
    int x, y;
    QFontMetricsF fm(this -> font()); // 设置字体规格
    double w,
    h,
    tmpVal;
    QString str;
    for (int i = 0; i <= m_scaleMajor; i++) {
        sina = sin(startRad - i * deltaRad);
        cosa = cos(startRad - i * deltaRad);
        tmpVal = 1.0 * i * ((m_maxValue - m_minValue) / m_scaleMajor) + m_minValue;
        str = QString("%1").arg(tmpVal); // %1作为占位符
        w = fm
            .size(Qt::TextSingleLine, str)
            .width();
        h = fm
            .size(Qt::TextSingleLine, str)
            .height();
        x = 90 * cosa - w / 2;
        y = -90 * sina + h / 4;
        painter -> drawText(x, y, str); // 函数的前两个参数是显示的坐标位置，后一个是显示的内容，是字符类型""
    }
    painter -> restore();
}

// 单位
void panel::drawTitle(QPainter * painter) {
    painter -> save();
    painter -> setPen(m_foreground);
    QString str(m_title); // 显示仪表的功能
    QFontMetricsF fm(this -> font());
    double w = fm
        .size(Qt::TextSingleLine, str)
        .width();
    painter -> drawText(static_cast<int>(-w / 2), -30, str);
    painter -> restore();
}

// 表针
void panel::drawIndicator(QPainter * painter) {
    painter -> save();
    QPolygon pts;
    pts.setPoints(3, -2, 0, 2, 0, 0, 60);
    /*(-2,0)/(2,0)/(0,60) */
    // 第一个参数是坐标的个数,后边的是坐标
    painter -> rotate(m_startAngle);
    double degRotate = (360.0 - m_startAngle - m_endAngle) / (
        m_maxValue - m_minValue
    ) * (m_value - m_minValue); // 画指针
    painter -> rotate(degRotate); // 顺时针旋转坐标系统

    painter -> setPen(QColor(171, 52, 0)); // 定义线条文本颜色  设置线条的颜色
    painter -> setBrush(QColor(171, 52, 0)); // 刷子定义形状如何填满 填充后的颜色

    painter -> drawConvexPolygon(pts); // 重载函数，绘制多边形。
    painter -> restore();
    // 画中心点
    QColor niceBlue(150, 150, 200);
    QConicalGradient coneGradient(0, 0, -90.0); // 角度渐变
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.2, niceBlue);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);
    painter -> setPen(Qt::NoPen); // 没有线，填满没有边界
    painter -> setBrush(coneGradient);
    painter -> drawEllipse(-5, -5, 10, 10);
}

// 数字显示
void panel::drawNumericalValue(QPainter * painter) {
    double tmp_value = m_value;
    QString str = QString("%1 %2")
        .arg(tmp_value, 0, 'f', m_precision)
        .arg(m_units);
    QFontMetricsF fm(font());
    double w = fm
        .size(Qt::TextSingleLine, str)
        .width();
    painter -> setPen(m_foreground);
    painter -> drawText(static_cast<int>(-w / 2), 72, str);
}

// 三色盘
void panel::drawColorPie(QPainter * painter) {
    int radius = 75;
    painter -> save();
    painter -> setPen(Qt::NoPen);
    QRectF rect(-radius, -radius, radius * 2, radius * 2);
    // 计算总范围角度,根据占比例自动计算三色圆环范围角度 可以更改比例
    double angleAll = 360.0 - m_startAngle - m_endAngle;
    double angleStart = angleAll * 0.5;
    double angleMid = angleAll * 0.2;
    double angleEnd = angleAll * 0.3;
    // 增加偏移量使得看起来没有脱节
    int offset = 3;
    // 绘制开始饼圆
    painter -> setBrush(pieColorStart);
    painter -> drawPie(
        rect,
        (270 - m_startAngle - angleStart) * 16,
        angleStart * 16
    );
    // 绘制中间饼圆(
    painter -> setBrush(pieColorMid);
    painter -> drawPie(
        rect,
        (270 - m_startAngle - angleStart - angleMid) * 16 + offset * 2,
        (angleMid + 0.05) * 16
    );
    // 绘制结束饼圆
    painter -> setBrush(pieColorEnd);
    painter -> drawPie(
        rect,
        (270 - m_startAngle - angleStart - angleMid - angleEnd - 2) * 16 + offset,
        angleEnd * 16
    );
    painter -> restore();
}

// 覆盖色
void panel::drawCoverCircle(QPainter * painter) {
    int radius = 60;
    painter -> save();
    painter -> setPen(Qt::NoPen);
    painter -> setBrush(coverCircleColor);
    painter -> drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter -> restore();
}

// 设置值边界
void panel::setValue(qreal value) {
    if (value > m_maxValue) {
        m_value = m_maxValue;
    } else if (value < m_minValue) {
        m_value = m_minValue;
    } else {
        m_value = value;
    }
    m_updateTimer -> start();
}

// 转动
void panel::UpdateAngle() {
    m_updateTimer -> stop();
    update();
}
