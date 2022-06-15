#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtGui>
#include <QString>
#include <QDebug>
#include <QDockWidget>
#include "SITE.h"
#include "ORGANIZATION.h"
#include <QAction>

extern SITE site;
extern Organization organization_info;


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
        for(int i=0;i<25;i++){
            cout<<i<<endl;
            cout<<site.info[i].organization_num<<","<<endl;
            for(int j=0;j<site.info[i].organization_num;j++){
                cout<<site.info[i].organization_no[j]<<site.info[i].organization[j]<<",";
            }
            cout<<endl<<site.info[i].location[0]<<","<<site.info[i].location[1]<<","<<endl;
            cout<<site.info[i].accessible_site_num<<","<<endl;
            for(int j=0;j<site.info[i].accessible_site_num;j++){
                cout<<site.info[i].accessible_site[j]<<","<<site.info[i].accessible_site_distance[site.info[i].accessible_site[j]]<<endl;
            }
            cout<<endl<<endl;
        }

//        for(int i=0;i<organization_info.organization_num;i++){
//            cout<<i<<endl;
//            cout<<organization_info.info[i].name<<","<<organization_info.info[i].site<<endl;
//            cout<<organization_info.info[i].location[0]<<","<<organization_info.info[i].location[1]<<endl;
//            cout<<organization_info.info[i].accessible_location_num<<endl;
//            for(int j=0;j<organization_info.info[i].accessible_location_num;j++){
//                cout<<organization_info.info[i].accessible_location[j]<<","<<organization_info.info[i].accessible_location_distance[j]<<",";
//            }
//        }


    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/pic/pic/icon.jpg"));
    this->setWindowTitle(QString("步行地图导航系统"));
    this->setFixedSize(1676,820);
    QPixmap pixmap(":/pic/pic/map.bmp");
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));
    this->setPalette(palette);
    this->setMask(pixmap.mask());
    this->setAutoFillBackground(true);

    for(int i=0;i<25;i++){
        MyButton[i] = new QToolButton(this);
        MyButton[i]->move(site.info[i].location[0], site.info[i].location[1]);
        MyButton[i]->resize(6,6);
        MyButton[i]->setStyleSheet("QToolButton{"
                                   "background-color:red;"
                                   "border-style:solid;"
                                   "border-width:0px;"
                                   "border-color:red;"
                                   "border-radius:3px;"
                                   "}");
        MyButton[i]->setAutoFillBackground(false);
        if(site.info[i].organization_num == 1){
            MyButton[i]->setToolTip(QString(i+'0')+QString("\n")+QString::fromLocal8Bit(site.info[i].organization[0]));
        }else{
            MyButton[i]->setToolTip(QString(i+'0')+QString("\n")+QString::fromLocal8Bit(site.info[i].organization[0])+QString("\n")+QString::fromLocal8Bit(site.info[i].organization[1]));
        }


        MyButton[i]->show();

    }
//    Search.show();
    connect(ui->actionSearch,&QAction::triggered,this,[=](){
        Search.show();
    });




}

MainWindow::~MainWindow()
{
    delete ui;
}

