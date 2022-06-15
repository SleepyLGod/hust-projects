#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTimer>
#include <QRect>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
using namespace std;

int matchString(string a,string b)
{
    int cnt=0;
    for(int i=0;i<b.length();i+=3)
    {
        for(int j=0;j<a.length();j+=3)
        {
            bool flag=true;
            if(i+2<b.length()&&j+2<a.length())
                for(int k=0;k<3;k++)
                    if(a[j+k]!=b[i+k])
                    {
                        flag=false;
                        break;
                    }
            if(flag)
            {
                cnt++;
                break;
            }
        }
    }
    return cnt;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setWindowFlag(Qt::WindowMaximizeButtonHint,false);
    ui->checkBox_2->setChecked(true);
    move(30,20);
    startPos.setX(0);
    startPos.setY(0);
    endPos.setX(0);
    endPos.setY(0);
    isClicked=false;
    bp=new busMap("source\\stops.txt","source\\lines.txt","source\\Organization.txt");
    connect(ui->action_Ctrl_R,&QAction::triggered,this,&MainWindow::findPointByName);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bp;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //draw map
    ui->mapFrame->setFixedHeight(820);
    ui->mapFrame->setFixedWidth(1676);
    QRect maprect=ui->mapFrame->frameRect();
    maprect.translate(ui->mapFrame->pos());
    QImage mapImage(":/source/hustMap.bmp");
    QPainter mapPainter(this);
    QPen mapPen;
    mapPainter.drawImage(maprect,mapImage);

    //draw stop points
    QRectF busStopsRect;
    mapPainter.setBrush(QColor(0,0,0));
    for(int i=1;i<=bp->getBusStopsNumber();i++)
    {
        myPoint *_p=bp->getBusStops()[i];
        busStopsRect.setTop(_p->getPosition().second+6);
        busStopsRect.setBottom(_p->getPosition().second-6);
        busStopsRect.setLeft(_p->getPosition().first-6);
        busStopsRect.setRight(_p->getPosition().first+6);
        mapPainter.drawEllipse(busStopsRect);
    }

    //draw start and end point
    if(startPos.x()!=0)
    {
        mapPen.setWidth(1);
        mapPen.setColor(Qt::red);
        mapPainter.setBrush(Qt::red);
        mapPainter.setPen(mapPen);
        busStopsRect.setTop(startPos.y()+6);
        busStopsRect.setBottom(startPos.y()-6);
        busStopsRect.setLeft(startPos.x()-6);
        busStopsRect.setRight(startPos.x()+6);
        mapPainter.drawEllipse(busStopsRect);
    }
    if(endPos.y()!=0)
    {
        mapPen.setColor(Qt::blue);
        mapPainter.setBrush(Qt::blue);
        mapPainter.setPen(mapPen);
        busStopsRect.setTop(endPos.y()+6);
        busStopsRect.setBottom(endPos.y()-6);
        busStopsRect.setLeft(endPos.x()-6);
        busStopsRect.setRight(endPos.x()+6);
        mapPainter.drawEllipse(busStopsRect);
    }

    //draw bus lines
    mapPainter.setBrush(Qt::NoBrush);
    mapPen.setWidth(3);
    mapPen.setColor(Qt::yellow);
    mapPen.setStyle(Qt::DotLine);
    mapPainter.setPen(mapPen);
    for(int i=1;i<=bp->getBusLinesNumber();i++)
        for(int j=1;j<bp->getEachBusLineNumber()[i];j++)
        {
            myPoint *_p1=bp->getBusStops()[bp->getBusLines()[i][j]];
            myPoint *_p2=bp->getBusStops()[bp->getBusLines()[i][j+1]];
            mapPainter.drawLine(_p1->getPosition().first,_p1->getPosition().second,
                                _p2->getPosition().first,_p2->getPosition().second);
        }

    //draw path
    int temp=endPointIndex;
    if(!ans || temp==0)
        return;

    mapPen.setWidth(3);
    mapPen.setColor(Qt::blue);
    mapPen.setStyle(Qt::SolidLine);
    mapPainter.setPen(mapPen);
    mapPainter.setBrush(Qt::NoBrush);
    mapPainter.drawLine(endPos.x(),endPos.y(),bp->getBusStops()[temp]->getPosition().first,
                        bp->getBusStops()[temp]->getPosition().second);
    while(ans[temp])
    {
        mapPainter.drawLine(bp->getBusStops()[temp]->getPosition().first,
                            bp->getBusStops()[temp]->getPosition().second,
                            bp->getBusStops()[ans[temp]]->getPosition().first,
                            bp->getBusStops()[ans[temp]]->getPosition().second);
        temp=ans[temp];
    }
    mapPainter.drawLine(startPos.x(),startPos.y(),bp->getBusStops()[temp]->getPosition().first,
                        bp->getBusStops()[temp]->getPosition().second);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    startPointIndex=0;
    endPointIndex=0;
    startPos.setX(0);
    startPos.setY(0);
    endPos.setX(0);
    endPos.setY(0);
    killTimer(timerId);
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePoint=event->pos();
    myPoint mousePointTemp;
    mousePointTemp.setPosition(mousePoint.x(),mousePoint.y());
    double minDistance=9999999.99;
    for(int i=1;i<=bp->getBusStopsNumber();i++)
    {
        double temp=calculateDistance(mousePointTemp,*bp->getBusStops()[i]);
        if(temp<minDistance)
        {
            if(!isClicked)
            {
                minDistance=temp;
                startPointIndex=i;
            }
            else
            {
                minDistance=temp;
                endPointIndex=i;
            }
        }
    }
    if(!isClicked)
    {
        isClicked=true;
        startPos=event->pos();
        endPos.setX(0);
        endPos.setY(0);
        repaint(ui->centralwidget->contentsRect());
        killTimer(timerId);
    }
    else
    {
        endPos=event->pos();
        if(ui->checkBox->isChecked())
            ans=bp->findDirectPath(startPointIndex,endPointIndex);
        else
            ans=bp->findEveryPath(startPointIndex,endPointIndex);
        repaint(ui->centralwidget->contentsRect());
        timerId=startTimer(5000);
        startPointIndex=0;
        endPointIndex=0;
        startPos.setX(0);
        startPos.setY(0);
        endPos.setX(0);
        endPos.setY(0);
        isClicked=false;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_R)
        findPointByName();
}

void MainWindow::findPointByName()
{
    Dialog *findPointDialog;
    findPointDialog=new Dialog(this);
    findPointDialog->show();
    findPointDialog->exec();
    string pointName=findPointDialog->pointName.toStdString();
    if(pointName.empty())
    {
        delete findPointDialog;
        return;
    }
    else
    {
        if(!isClicked)
        {
            int maxCnt=0;
            int ansIndex=0;
            for(int i=1;i<=bp->getOrganizationsNumber();i++)
            {
                if(matchString(bp->getOrganizationNames()[i],pointName)>maxCnt)
                {
                    maxCnt=matchString(bp->getOrganizationNames()[i],pointName);
                    ansIndex=i;
                }
            }
            if(ansIndex==0)
            {
                delete findPointDialog;
                QMessageBox tempMessageBox(QMessageBox::Critical,"查找失败","未查找到地点！",QMessageBox::Ok,this);
                tempMessageBox.exec();
                return;
            }
            killTimer(timerId);
            isClicked=true;
            startPos.setX(bp->getOrganizationPos()[ansIndex].first);
            startPos.setY(bp->getOrganizationPos()[ansIndex].second);
            myPoint startPointTemp;
            startPointTemp.setPosition(startPos.x(),startPos.y());
            double minDistance=9999999.99;
            for(int i=1;i<=bp->getBusStopsNumber();i++)
            {
                double temp=calculateDistance(startPointTemp,*bp->getBusStops()[i]);
                if(temp<minDistance)
                {
                    minDistance=temp;
                    startPointIndex=i;
                }
            }
            repaint(ui->centralwidget->contentsRect());
        }
        else
        {
            int maxCnt=0;
            int ansIndex=0;
            for(int i=1;i<=bp->getOrganizationsNumber();i++)
            {
                if(matchString(bp->getOrganizationNames()[i],pointName)>maxCnt)
                {
                    maxCnt=matchString(bp->getOrganizationNames()[i],pointName);
                    ansIndex=i;
                }
            }
            if(ansIndex==0)
            {
                delete findPointDialog;
                QMessageBox tempMessageBox(QMessageBox::Critical,"查找失败","未查找到地点！",QMessageBox::Ok,this);
                tempMessageBox.exec();
                return;
            }
            endPos.setX(bp->getOrganizationPos()[ansIndex].first);
            endPos.setY(bp->getOrganizationPos()[ansIndex].second);
            myPoint endPointTemp;
            endPointTemp.setPosition(endPos.x(),endPos.y());
            double minDistance=9999999.99;
            for(int i=1;i<=bp->getBusStopsNumber();i++)
            {
                double temp=calculateDistance(endPointTemp,*bp->getBusStops()[i]);
                if(temp<minDistance)
                {
                    minDistance=temp;
                    endPointIndex=i;
                }
            }
            if(ui->checkBox->isChecked())
                ans=bp->findDirectPath(startPointIndex,endPointIndex);
            else
                ans=bp->findEveryPath(startPointIndex,endPointIndex);
            repaint(ui->centralwidget->contentsRect());
            timerId=startTimer(5000);
            startPointIndex=0;
            endPointIndex=0;
            isClicked=false;
        }
    }
    delete findPointDialog;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked())
        ui->checkBox_2->setChecked(false);
    else
        ui->checkBox_2->setChecked(true);
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(ui->checkBox_2->isChecked())
        ui->checkBox->setChecked(false);
    else
        ui->checkBox->setChecked(true);
}

