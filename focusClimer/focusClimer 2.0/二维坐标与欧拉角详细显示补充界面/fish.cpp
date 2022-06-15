#include "fish.h"
#include "ui_fish.h"
#include <QPushButton>
#include <QTimer>
#include <QSplitter>
#include <QDateTime>
#include <QColorDialog>
fish::fish(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fish)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();

    //平面图散点数据分配空间
    seriesLine = new QSplineSeries(); //光滑曲线序列
    seriesLine1 = new QSplineSeries();
    seriesLine2 = new QSplineSeries();
    series0 = new QScatterSeries();
    series1 = new QScatterSeries();
    series2 = new QScatterSeries();

    //三维图点的数据分配空间
    graph3D = new Q3DScatter();
    graphContainer = QWidget::createWindowContainer(graph3D); //Q3DBars继承自QWindow，必须如此创建
    QScatterDataProxy *proxy = new QScatterDataProxy(); //数据代理
    series = new QScatter3DSeries(proxy);  //创建序列，问题的关键

    //信号与槽，创建定时器
    timer_t = new QTimer(this);
    connect(timer_t,SIGNAL(timeout()),this,SLOT(iniGraph3D()));
    connect(timer_t,SIGNAL(timeout()),this,SLOT(buildScatterChart()));

    //界面布局，创建3区分割
    QSplitter *m_splitter = new QSplitter(Qt::Horizontal, this);
    QSplitter *splitter1 = new QSplitter(Qt::Vertical);
//    m_splitter->addWidget(ui->groupBox);
    m_splitter->addWidget(splitter1);
    splitter1->addWidget(graphContainer);
    splitter1->addWidget(ui->groupBox_2);
    QGridLayout *mainly = new QGridLayout;
    mainly->addWidget(m_splitter);
    this->setLayout(mainly);
    this->setCentralWidget(m_splitter);

}

//二维散点图初始化
void fish::iniScatterChart()
{
    QChart *chart = new QChart();
    QChart *chart_1 = new QChart();
    QChart *chart_2 = new QChart();

    chart->setTitle("爬壁机器人在XY平面运动演示");
    chart_1->setTitle("爬壁机器人在XZ平面运动演示 演示");
    chart_2->setTitle("爬壁机器人在YZ平面运动演示演示");

    chart->setAnimationOptions(QChart::AllAnimations);
    chart_1->setAnimationOptions(QChart::AllAnimations);
    chart_2->setAnimationOptions(QChart::AllAnimations);

    ui->chartViewScatter_1->setChart(chart);
    ui->chartViewScatter_1->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView->setChart(chart_1);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView_2->setChart(chart_2);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
}

 //绘制各个平面的QScatterSeries和QSplineSeries图
void fish::buildScatterChart()
{
    QChart *chart =ui->chartViewScatter_1->chart();
    QChart *chart_1 =ui->graphicsView->chart();
    QChart *chart_2 =ui->graphicsView_2->chart();

    chart->setTheme(QChart::ChartThemeBlueIcy);
    chart_1->setTheme(QChart::ChartThemeQt);
    chart_2->setTheme(QChart::ChartThemeLight);

    chart->removeAxis(chart->axisX());
    chart->removeAxis(chart->axisY());

    chart_1->removeAxis(chart->axisX());
    chart_1->removeAxis(chart->axisY());

    chart_2->removeAxis(chart->axisX());
    chart_2->removeAxis(chart->axisY());

    seriesLine->setName("spline");
    seriesLine1->setName("spline");
    seriesLine2->setName("spline");

    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    seriesLine->setColor(Qt::red);
    seriesLine1->setColor(Qt::green);
    seriesLine2->setPen(pen);

    //散点序列
    series0->setName("散点");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);//MarkerShapeRectangle,MarkerShapeCircle
    series0->setBorderColor(Qt::black);
    series0->setBrush(QBrush(Qt::yellow));
    series0->setMarkerSize(10);

    series1->setName("散点");
    series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);//MarkerShapeRectangle,MarkerShapeCircle
    series1->setBorderColor(Qt::white);
    series1->setBrush(QBrush(Qt::red));
    series1->setMarkerSize(10);

    series2->setName("散点");
    series2->setMarkerShape(QScatterSeries::MarkerShapeCircle);//MarkerShapeRectangle,MarkerShapeCircle
    series2->setBorderColor(Qt::gray);
    series2->setBrush(QBrush(Qt::darkCyan));
    series2->setMarkerSize(10);

    QString displaystring_MES;
    QFile file_MES("D:/optitrack_data.txt");       //打开路径，可以修改此处的路径读取不同地方的文件
    if(!file_MES.open(QIODevice::ReadOnly|QIODevice::Text))   //如果遇到无法打开的情况
       {
           qDebug()<<"can not open the file"<<endl;
       }
       while(!file_MES.atEnd())
       {
           QByteArray  line_MES = file_MES.readLine();
           QString str_MES(line_MES);

           //刚体和靶标数值显示

           //刚体1（工件）和靶标的数据显示
           if(str_MES[0] == "R" && str_MES[15]=="1" )
           {
              QString  str1= str_MES.section("\t",1,1);
              QString  str2= str_MES.section("\t",2,2);
              QString  str3= str_MES.section("\t",3,3);
              /*ui->lineEdit->setText(str1);
              ui->lineEdit_2->setText(str2);
              ui->lineEdit_3->setText(str1);
              ui->lineEdit_4->setText(str3);
              ui->lineEdit_5->setText(str2);
              ui->lineEdit_6->setText(str3);*/
              M=str1.toDouble();
              S=str2.toDouble();
              E=str3.toDouble();
              qDebug() << M<<endl;
              qDebug() << E<<endl;
              *series0<<QPointF(M,S);
              *seriesLine<<QPointF(M,S);
              *series1<<QPointF(M,E);
              *seriesLine1<<QPointF(M,E);
              *series2<<QPointF(S,E);
              *seriesLine2<<QPointF(S,E);
           }

           chart->addSeries(series0);
           chart->addSeries(seriesLine);

           chart_1->addSeries(series1);
           chart_1->addSeries(seriesLine1);

           chart_2->addSeries(series2);
           chart_2->addSeries(seriesLine2);

           chart->createDefaultAxes(); //创建缺省的坐标轴
           chart_1->createDefaultAxes();
           chart_2->createDefaultAxes();

           QValueAxis *axisX=(QValueAxis *)ui->chartViewScatter_1->chart()->axisX();
           axisX->setTickCount(11);
           axisX->setMinorTickCount(2);
           axisX->setTitleText("X轴");
           axisX->setRange(0,5);
           axisX->setLabelFormat("%.1f");
           //设置X轴字体大小
           QFont font0=axisX->labelsFont();
           font0.setPointSize(7);
           axisX->setTitleFont(font0);

           QValueAxis *axisY=(QValueAxis *)ui->chartViewScatter_1->chart()->axisY();
           axisY->setTickCount(11);
           axisY->setMinorTickCount(2);
           axisY->setTitleText("Y轴");
           axisY->setRange(0,5);
           axisY->setLabelFormat("%.1f");
           //设置Y轴字体大小
           QFont font01=axisY->labelsFont();
           font01.setPointSize(7);
           axisY->setTitleFont(font01);

           QValueAxis *axisX1=(QValueAxis *)ui->graphicsView->chart()->axisX();
           axisX1->setTickCount(11);
           axisX1->setMinorTickCount(2);
           axisX1->setTitleText("X轴");
           axisX1->setRange(0,5);
           axisX1->setLabelFormat("%.1f");

           QValueAxis *axisY1=(QValueAxis *)ui->graphicsView->chart()->axisY();
           axisY1->setTickCount(11);
           axisY1->setMinorTickCount(2);
           axisY1->setTitleText("Z轴");
           axisY1->setRange(0,5);
           axisY1->setLabelFormat("%.1f");

           QValueAxis *axisX2=(QValueAxis *)ui->graphicsView_2->chart()->axisX();
           axisX2->setTickCount(11);
           axisX2->setMinorTickCount(2);
           axisX2->setTitleText("Y轴");
           axisX2->setRange(0,5);
           axisX2->setLabelFormat("%.1f");

           QValueAxis *axisY2=(QValueAxis *)ui->graphicsView_2->chart()->axisY();
           axisY2->setTickCount(11);
           axisY2->setMinorTickCount(2);
           axisY2->setTitleText("Z轴");
           axisY2->setRange(0,5);
           axisY2->setLabelFormat("%.1f");

    foreach (QLegendMarker* marker, chart->legend()->markers()) {
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(on_chartBarLegendMarkerClicked()));
        QObject::connect(marker, SIGNAL(clicked()), this, SLOT(on_chartBarLegendMarkerClicked()));
    }
    foreach (QLegendMarker* marker, chart_1->legend()->markers()) {
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
        QObject::connect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
    }
    foreach (QLegendMarker* marker, chart_2->legend()->markers()) {
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(on_chart_2Clicked()));
        QObject::connect(marker, SIGNAL(clicked()), this, SLOT(on_chart_2Clicked()));
    }
         }
}
//散点与线是否显示槽函数
void fish::on_chartBarLegendMarkerClicked()
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());

    switch (marker->type())
    {
        case QLegendMarker::LegendMarkerTypeXY:
        {
            marker->series()->setVisible(!marker->series()->isVisible());
            marker->setVisible(true);
            marker->setVisible(true);
            qreal alpha = 1.0;
            if (!marker->series()->isVisible())
                alpha = 0.5;

            QColor color;
            QBrush brush = marker->labelBrush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setLabelBrush(brush);

            brush = marker->brush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setBrush(brush);

            QPen pen = marker->pen();
            color = pen.color();
            color.setAlphaF(alpha);
            pen.setColor(color);
            marker->setPen(pen);
            break;
        }
    default:
        break;
    }

}

void fish::on_LegendMarkerClicked()
{//点击图例的marker的响应
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());

    switch (marker->type()) //marker的类型
    {
        case QLegendMarker::LegendMarkerTypeXY: //QLineSeries序列的图例marker
        {
            marker->series()->setVisible(!marker->series()->isVisible()); //可见性
            marker->setVisible(true);
            qreal alpha = 1.0;
            if (!marker->series()->isVisible())
                alpha = 0.5;

            QColor color;
            QBrush brush = marker->labelBrush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setLabelBrush(brush);

            brush = marker->brush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setBrush(brush);

            QPen pen = marker->pen();
            color = pen.color();
            color.setAlphaF(alpha);
            pen.setColor(color);
            marker->setPen(pen);
            break;
        }
        default:
            break;
    }
}

void fish::on_chart_2Clicked()
{//点击图例的marker的响应
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());

    switch (marker->type()) //marker的类型
    {
        case QLegendMarker::LegendMarkerTypeXY: //QLineSeries序列的图例marker
        {
            marker->series()->setVisible(!marker->series()->isVisible()); //可见性
            marker->setVisible(true);
            qreal alpha = 1.0;
            if (!marker->series()->isVisible())
                alpha = 0.5;

            QColor color;
            QBrush brush = marker->labelBrush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setLabelBrush(brush);

            brush = marker->brush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setBrush(brush);

            QPen pen = marker->pen();
            color = pen.color();
            color.setAlphaF(alpha);
            pen.setColor(color);
            marker->setPen(pen);
            break;
        }
        default:
            break;
    }
}


fish::~fish()
{
    delete ui;
}
void fish::on_pushButton_clicked()
{
timer_t->start(500);

}
void fish::on_chkBoxGrid_clicked(bool checked)
{ //图表的网格
    graph3D->activeTheme()->setGridEnabled(checked);
}

void fish::on_chkBoxSmooth_clicked(bool checked)
{ //柱状图的光滑性
    series->setMeshSmooth(checked);
}

void fish::on_chkBoxReflection_clicked(bool checked)
{//反射
    graph3D->setReflection(checked);
}

void fish::on_chkBoxAxisTitle_clicked(bool checked)
{//轴标题
    graph3D->axisX()->setTitleVisible(checked);
    graph3D->axisY()->setTitleVisible(checked);
    graph3D->axisZ()->setTitleVisible(checked);
}

void fish::on_chkBoxAxisBackground_clicked(bool checked)
{//轴标题背景
    graph3D->activeTheme()->setLabelBackgroundEnabled(checked);
}

void fish::on_chkBoxReverse_clicked(bool checked)
{//Z轴反向
    graph3D->axisZ()->setReversed(checked);
}

void fish::on_chkBoxBackground_clicked(bool checked)
{//图表的背景
    graph3D->activeTheme()->setBackgroundEnabled(checked);
}

void fish::on_spinFontSize_valueChanged(int arg1)
{//轴标签字体大小
    QFont font = graph3D->activeTheme()->font();
    font.setPointSize(arg1);
    graph3D->activeTheme()->setFont(font);
}

void fish::on_cBoxTheme_currentIndexChanged(int index)
{//设置主题
    Q3DTheme *currentTheme = graph3D->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(index));
}

void fish::on_btnBarColor_clicked()
{ //设置序列柱状图的颜色
    QColor  color=series->baseColor();
    color=QColorDialog::getColor(color);
    if (color.isValid())
        series->setBaseColor(color);
}

void fish::on_chkBoxItemLabel_clicked(bool checked)
{ //项的标签
    series->setItemLabelVisible(checked);
}

void fish::on_cBoxBarStyle_currentIndexChanged(int index)
{ //棒图的样式
    QAbstract3DSeries::Mesh aMesh;
    aMesh=QAbstract3DSeries::Mesh(index+1);
    series->setMesh(aMesh);
}

void fish::on_cBoxSelectionMode_currentIndexChanged(int index)
{//选择模式
    graph3D->setSelectionMode(QAbstract3DGraph::SelectionFlags(index));
}

void fish::on_spinItemSize_valueChanged(double arg1)
{
    series->setItemSize(arg1);//default 0. value 0~1
}

void fish::on_chkBoxShadow_clicked(bool checked)
{
    if (checked)
       graph3D->setShadowQuality(QAbstract3DGraph::ShadowQualityMedium);
    else
       graph3D->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
}

void fish::on_comboBox_currentIndexChanged(int index)
{
    graph3D->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPreset(index));
}

void fish::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
//    int xRot =ui->sliderH->value();
//    int yRot=ui->sliderV->value();
//    int zoom=ui->sliderZoom->value(); //缩放
//    graph3D->scene()->activeCamera()->setCameraPosition(xRot, yRot,zoom);
}

void fish::on_sliderV_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

void fish::on_sliderZoom_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}

void fish::iniGraph3D(){

    series->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
    series->setMeshSmooth(true);
    series->setBaseColor(Qt::blue);
    //创建坐标轴
    graph3D->axisX()->setTitle("axis X");
    graph3D->axisX()->setTitleVisible(true);
    graph3D->axisY()->setTitle("axis Y");
    graph3D->axisY()->setTitleVisible(true);
    graph3D->axisZ()->setTitle("axis Z");
    graph3D->axisZ()->setTitleVisible(true);
    graph3D->axisX()->setRange(0,5);
    graph3D->axisY()->setRange(0,5);
    graph3D->axisZ()->setRange(0,5);
    //graph3D->setHorizontalAspectRatio(2.0);//水平纵横比是x轴与z轴之间的图形比例，默认0.0，表示根据轴范围自动缩放
    //graph3D->setAspectRatio(1);//设置水平面最长轴与y轴之间的图形比例，默认为2

    //关闭各个轴的自调节
    graph3D->axisX()->setAutoAdjustRange(false);
    graph3D->axisY()->setAutoAdjustRange(false);
    graph3D->axisZ()->setAutoAdjustRange(false);
    //坐标轴分三大段
    graph3D->axisX()->setSegmentCount(11);
    graph3D->axisY()->setSegmentCount(11);
    graph3D->axisZ()->setSegmentCount(11);
    //设置坐标轴数量,每小段数量
    graph3D->axisX()->setSubSegmentCount(2);
    graph3D->axisY()->setSubSegmentCount(2);
    graph3D->axisZ()->setSubSegmentCount(2);
    graph3D->activeTheme()->setLabelBackgroundEnabled(false);
    series->setMesh(QAbstract3DSeries::MeshSphere); //MeshPoint, MeshCylinder
    series->setItemSize(0.2f);//default 0. value 0~1
    //QScatterDataProxy *proxy = new QScatterDataProxy(); //数据代理
    //series = new QScatter3DSeries(proxy);  //创建序列，问题的关键
    QScatterDataArray dataArray ;
    QString displaystring_MES;
    QFile file_MES("D:/optitrack_data.txt");       //打开路径，可以修改此处的路径读取不同地方的文件
    if(!file_MES.open(QIODevice::ReadOnly|QIODevice::Text))   //如果遇到无法打开的情况
    {
        qDebug()<<"can not open the file"<<endl;
    }
    while(!file_MES.atEnd())
    {
        QByteArray  line_MES = file_MES.readLine();
        QString str_MES(line_MES);

        //刚体和靶标数值显示

        //刚体1（工件）和靶标的数据显示
        if(str_MES[0] == "R" && str_MES[15]=="1" )
        {
            QString  str1= str_MES.section("\t",1,1);
            QString  str2= str_MES.section("\t",2,2);
            QString  str3= str_MES.section("\t",3,3);
            ui->lineEdit_1->setText(str1);
            ui->lineEdit_2->setText(str2);
            ui->lineEdit_3->setText(str3);
            M=str1.toDouble();
            S=str2.toDouble();
            E=str3.toDouble();
            dataArray<<QVector3D(M,S,E);
            series->dataProxy()->addItems(dataArray);
            graph3D->addSeries(series);
            //qDebug()<<"数组大小是： "<<graph3D->seriesList().size();
            //if (graph3D->seriesList().size())
            // graph3D->seriesList().removeFirst();
        }
        //qDebug()<<"外面数组大小是： "<<graph3D->seriesList().size();
    }
    //qDebug()<<"最外面数组大小是： "<<graph3D->seriesList().size();

   }


void fish::on_pushButton_2_clicked()
{
    timer_t->stop();
}


