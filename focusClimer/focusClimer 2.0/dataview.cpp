//#include "dataview.h"
#include "ClimbotWin.h"
#include <QPushButton>
#include <QTimer>
#include <QSplitter>
#include <QDateTime>
#include <QColorDialog>
#include "ui_ClimbotWin.h"

/*
 *  一代机暂时取消二维坐标系的绘制
 *
//绘制各个平面的QScatterSeries和QSplineSeries图
void ClimbotWin::buildScatterChart()
{
    QChart *chart =ui->graphicsView_xy->chart();
    QChart *chart_1 =ui->graphicsView_xz->chart();
    QChart *chart_2 =ui->graphicsView_yz->chart();

    chart->setTheme(QChart::ChartThemeBlueIcy);
    chart_1->setTheme(QChart::ChartThemeBlueIcy);
    chart_2->setTheme(QChart::ChartThemeBlueIcy);

//    chart->removeAxis(chart->axisX());
//    chart->removeAxis(chart->axisY());

//    chart_1->removeAxis(chart->axisX());
//    chart_1->removeAxis(chart->axisY());

//    chart_2->removeAxis(chart->axisX());
//    chart_2->removeAxis(chart->axisY());

    seriesLine->setName("Spline");
    seriesLine1->setName("Spline");
    seriesLine2->setName("Spline");

    seriesLine->setColor(Qt::green);
    seriesLine1->setColor(Qt::red);
    seriesLine2->setColor(Qt::blue);

    //散点序列
    series0->setName("Point");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);//MarkerShapeRectangle,MarkerShapeCircle
    series0->setBorderColor(Qt::black);
    series0->setBrush(QBrush(Qt::yellow));
    series0->setMarkerSize(8);

    series1->setName("Point");
    series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);//MarkerShapeRectangle,MarkerShapeCircle
    series1->setBorderColor(Qt::black);
    series1->setBrush(QBrush(Qt::red));
    series1->setMarkerSize(8);

    series2->setName("Point");
    series2->setMarkerShape(QScatterSeries::MarkerShapeCircle);//MarkerShapeRectangle,MarkerShapeCircle
    series2->setBorderColor(Qt::black);
    series2->setBrush(QBrush(Qt::blue));
    series2->setMarkerSize(8);

    QFile file_MES("./optitrack_data.txt");       //打开路径，可以修改此处的路径读取不同地方的文件
    if(!file_MES.open(QIODevice::ReadOnly|QIODevice::Text))   //如果遇到无法打开的情况
    {
        qDebug()<<"can not open the file"<<endl;
        UpdateInfo("Normal","The filepath is wrong");
    }
    while(!file_MES.atEnd())
    {
        QByteArray line_MES = file_MES.readLine();
        QString str_MES(line_MES);
        //刚体和靶标数值显示
        //刚体1（工件）和靶标的数据显示
        if(str_MES[0] == "R" && str_MES[15]=="1" )
        {
            QString  str1= str_MES.section("\t",1,1);
            QString  str2= str_MES.section("\t",2,2);
            QString  str3= str_MES.section("\t",3,3);

            m_M=str1.toDouble();//x
            m_S=str2.toDouble();//y
            m_E=str3.toDouble();//z

            *series0<<QPointF(m_M,m_S);
            *seriesLine<<QPointF(m_M,m_S);

            *series1<<QPointF(m_M,m_E);
            *seriesLine1<<QPointF(m_M,m_E);

            *series2<<QPointF(m_S,m_E);
            *seriesLine2<<QPointF(m_S,m_E);
        }

        chart->addSeries(series0);
        chart->addSeries(seriesLine);

        chart_1->addSeries(series1);
        chart_1->addSeries(seriesLine1);

        chart_2->addSeries(series2);
        chart_2->addSeries(seriesLine2);
        //创建缺省的坐标轴
        chart->createDefaultAxes();
        chart_1->createDefaultAxes();
        chart_2->createDefaultAxes();


        QValueAxis *axisX=static_cast<QValueAxis *>(ui->graphicsView_xy->chart()->axisX());

        axisX->setTickCount(5);
        axisX->setMinorTickCount(1);
        axisX->setTitleText("X轴");
        axisX->setRange(0,5);
        axisX->setLabelFormat("%.1f");


        QValueAxis *axisY=static_cast<QValueAxis *>(ui->graphicsView_xy->chart()->axisY());
        axisY->setTickCount(5);
        axisY->setMinorTickCount(1);
        axisY->setTitleText("Y轴");
        axisY->setRange(0,5);
        axisY->setLabelFormat("%.1f");

        //设置X轴字体大小
        QFont font0=axisX->labelsFont();
        font0.setPointSize(6);
        axisX->setTitleFont(font0);
        //设置Y轴字体大小
        QFont font01=axisY->labelsFont();
        font01.setPointSize(6);
        axisY->setTitleFont(font01);

        QValueAxis *axisX1=static_cast<QValueAxis *>(ui->graphicsView_xz->chart()->axisX());
        axisX1->setTickCount(5);
        axisX1->setMinorTickCount(1);
        axisX1->setTitleText("X轴");
        axisX1->setRange(0,5);
        axisX1->setLabelFormat("%.1f");


        QValueAxis *axisY1=static_cast<QValueAxis *>(ui->graphicsView_xz->chart()->axisY());
        axisY1->setTickCount(5);
        axisY1->setMinorTickCount(1);
        axisY1->setTitleText("Z轴");
        axisY1->setRange(0,5);
        axisY1->setLabelFormat("%.1f");

        //设置X1轴字体大小
        axisX1->setTitleFont(font0);
        //设置Y1轴字体大小
        axisY1->setTitleFont(font01);

        QValueAxis *axisX2=static_cast<QValueAxis *>(ui->graphicsView_yz->chart()->axisX());
        axisX2->setTickCount(5);
        axisX2->setMinorTickCount(1);
        axisX2->setTitleText("Y轴");
        axisX2->setRange(0,5);
        axisX2->setLabelFormat("%.1f");

        QValueAxis *axisY2=static_cast<QValueAxis *>(ui->graphicsView_yz->chart()->axisY());
        axisY2->setTickCount(5);
        axisY2->setMinorTickCount(1);
        axisY2->setTitleText("Z轴");
        axisY2->setRange(0,5);
        axisY2->setLabelFormat("%.1f");

        //设置X1轴字体大小
        axisX2->setTitleFont(font0);
        //设置Y1轴字体大小
        axisY2->setTitleFont(font01);
    }
}
*/
//绘制三维图像
//void ClimbotWin::iniGraph3D()
//{

//    //图表的网格
//    graph3D->activeTheme()->setGridEnabled(1);
//    //柱状图的光滑性
//    series_3D->setMeshSmooth(1);
//    //反射
//    graph3D->setReflection(1);

//    //轴标题
//    graph3D->axisX()->setTitleVisible(1);
//    graph3D->axisY()->setTitleVisible(1);
//    graph3D->axisZ()->setTitleVisible(1);

//    //轴标签字体大小
//    QFont font = graph3D->activeTheme()->font();
//    font.setPointSize(1);
//    graph3D->activeTheme()->setFont(font);
//    //轴标题背景
//    graph3D->activeTheme()->setLabelBackgroundEnabled(1);

//    //图表的背景
//    graph3D->activeTheme()->setBackgroundColor("white");
//    graph3D->activeTheme()->setBackgroundEnabled(1);
//    //Z轴反向
//    graph3D->axisZ()->setReversed(1);

//    //阴影的标签
//    graph3D->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

//    //数据设置
//    series_3D->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
//    series_3D->setMeshSmooth(true);
//    series_3D->setBaseColor(Qt::blue);

//    //创建坐标轴
//    graph3D->axisX()->setTitle("axis X");
//    graph3D->axisY()->setTitle("axis Y");
//    graph3D->axisZ()->setTitle("axis Z");

//    //轴的值范围
//    graph3D->axisX()->setRange(0,5);//（min,max）
//    graph3D->axisY()->setRange(0,5);
//    graph3D->axisZ()->setRange(0,5);

//    //graph3D->setHorizontalAspectRatio(2.0);
//    //水平纵横比是x轴与z轴之间的图形比例，默认0.0，表示根据轴范围自动缩放
//    //graph3D->setAspectRatio(1);//设置水平面最长轴与y轴之间的图形比例，默认为2
//    //关闭各个轴的自调节
//    graph3D->axisX()->setAutoAdjustRange(false);
//    graph3D->axisY()->setAutoAdjustRange(false);
//    graph3D->axisZ()->setAutoAdjustRange(false);

//    //坐标轴分三大段
//    graph3D->axisX()->setSegmentCount(5);
//    graph3D->axisY()->setSegmentCount(5);
//    graph3D->axisZ()->setSegmentCount(5);

//    //设置坐标轴数量,每小段数量
//    graph3D->axisX()->setSubSegmentCount(2);//每个段内有2个子段
//    graph3D->axisY()->setSubSegmentCount(2);
//    graph3D->axisZ()->setSubSegmentCount(2);
//    graph3D->activeTheme()->setLabelBackgroundEnabled(false);//无背景
//    series_3D->setMesh(QAbstract3DSeries::MeshSphere); //MeshPoint, MeshCylinder
//    series_3D->setItemSize(0.2f);//Item size for the series.（default 0. value 0~1）

//}

//void ClimbotWin::BuildGraph3D()
//{
//    iniGraph3D();
//    QScatterDataArray dataArray ;
//    QFile file_MES("./optitrack_data.txt"); //打开路径，可以修改此处的路径读取不同地方的文件
//    //如果遇到无法打开的情况
//    if(!file_MES.open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        UpdateInfo("Normal","The filepath is wrong!");
//        qDebug()<<"can not open the file"<<Qt::endl;
//    }
//    //已打开且还未到达文件末尾时
//    while(!file_MES.atEnd())
//    {
//        QByteArray  line_MES = file_MES.readLine();
//        //读取一行ASCII字符，最大长度为maxSize-1个字节，将字符存储在数据中，并返回读取的字节数。
//        QString str_MES(line_MES);
//        //刚体1（工件）和靶标的数据显示
//                if(str_MES[0] == "R" && str_MES[15]=="1" )
//                {
//                    //返回部分字符串
//                    QString  str1= str_MES.section("\t",1,1);
//                    QString  str2= str_MES.section("\t",2,2);
//                    QString  str3= str_MES.section("\t",3,3);
//                    QString  str4= str_MES.section("\t",4,4);
//                    QString  str5= str_MES.section("\t",5,5);
//                    QString  str6= str_MES.section("\t",6,6);
//                    QString  str7= str_MES.section("\t",7,7);

//                    ui->lineEdit->setText(str1);
//                    ui->lineEdit_13->setText(str2);
//                    ui->lineEdit_14->setText(str3);

//                    M=str1.toFloat();
//                    S=str2.toFloat();
//                    E=str3.toFloat();

//                    A=str4.toDouble();
//                    B=str5.toDouble();
//                    C=str6.toDouble();
//                    D=str7.toDouble();

//                    H=(A*D*2+2*B*C)/(A*A+B*B-C*C-D*D);//arctan偏航角
//                    I=(2*B*D-2*A*C);//arcsin俯仰角
//                    J=(C*D*2+2*B*A)/(A*A-B*B-C*C+D*D);//arctan翻滚角

//                    G=qAtan(H);//偏航角
//                    R=qAtan(J);//翻滚角
//                    T=-qAsin(I);//俯仰角

//                    F=G*57.29578 ;//将偏航角转为角度制
//                    r=R*57.29578;//将翻滚角转为角度制
//                    t=T*57.29578;//将俯仰角转为角度制

//                    QString str8 = QString("%1").arg(F);//偏航角转为文字
//                    QString str9 = QString("%1").arg(t);//俯仰角转为文字
//                    QString str10 = QString("%1").arg(r);//翻滚角转为文字

//                    ui->lineEdit_15->setText(str8);//偏航角
//                    ui->lineEdit_16->setText(str9);//俯仰角
//                    ui->lineEdit_17->setText(str10);//翻滚角

//                    dataArray<<QVector3D(M,S,E);
//                    series_3D->dataProxy()->addItems(dataArray);
//                    graph3D->addSeries(series_3D);

//                }

//        if(str_MES[0] == "f" && str_MES[1]=="a" )
//        {
//            QString fan1=str_MES.section("\t",1,1);
//            QString fan2=str_MES.section("\t",2,2);
//            QString fan3=str_MES.section("\t",3,3);
//        }

//         if(str_MES[0]=='p'&&str_MES[1]=='o'&&str_MES[2]=='s')
//        {
//            QString strx=str_MES.section("\t",1,1);
//            QString stry=str_MES.section("\t",2,2);
//            QString stryaw=str_MES.section("\t",3,3);

//            ui->lineEdit->setText(strx);
//            ui->lineEdit_13->setText(stry);
//            ui->lineEdit_17->setText(stryaw);
//        }

//    }
//}

