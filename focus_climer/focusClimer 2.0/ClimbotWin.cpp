#include "ClimbotWin.h"
#include "ui_ClimbotWin.h"
#include <filepath.h>
#include "QDebug"
#include <QTime>
#include <QTimer>
#include <QProcess>
#include "dataview.h"
#include <QHostAddress>
#include <QFile>
#include <QLineEdit>

ClimbotWin::ClimbotWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClimbotWin) {
    ui->setupUi(this);
    ui->InfoTable->setColumnWidth(2, 500);
    UpdateInfo("Normal", "start");
    ConRbt = new ConnectRobot(SettingFilePath);
    UpdateInfo("Normal", "Loading settings");
    BeauCli();
    Panelinit();
    DataviewInit();
    loadDobotModel();
    // 显示当前时间
    QDateTime current_time =QDateTime::currentDateTime();
    QString filename = current_time.toString("yyyy-MM-dd-HH-mm-ss") + ".txt";
    file = new QFile(filename);
    control = 0;

    /*
    // 测试(废)
     QTimer* timer = new QTimer(this);
     connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
     timer->start(1000);
     startTimer(2000);
     startTimer(5500);
     startTimer(10500);
    // 测试（新）
     tim = new QTimer();
     tim->setInterval(1000);
     connect(tim,SIGNAL(timeout()),this,SLOT(onTimeOut()));
     tim->start();
     */

}

// 清空饼状图与图像
ClimbotWin::~ClimbotWin() {
    delete panel1;
    delete panel2;
    delete panel3;
    delete graph3D;
    delete ui;
}



void ClimbotWin::UpdateInfo(QString Type, QString data) {
    QDateTime current_time =QDateTime::currentDateTime();
    // 基于项目的表视图
    ui->InfoTable->insertRow(0);
    ui->InfoTable->setItem(0,0,new QTableWidgetItem(current_time.toString( "yyyy-MM-dd HH:mm:ss")))) // 时间
    ui->InfoTable->setItem(0,1,new QTableWidgetItem(Type)); // 类型
    ui->InfoTable->setItem(0,2,new QTableWidgetItem(data)); // 消息
}

void ClimbotWin::BeauCli() {
    // 连接功能键
    // 左侧按钮
    ui->ConnectBtn->setToolTip( "连接设备"))
    ui->FinishBtn->setToolTip( "停止工作"))
    ui->EngineStartBtn->setToolTip( "风机开启"))
    ui->EngineStopBtn->setToolTip( "风机关闭"))
    ui->pushButton_10->setToolTip( "打磨头开启"))
    ui->pushButton_11->setToolTip( "打磨头关闭"))

    // 二维位置监测表
    ui->lineEdit->setReadOnly(1);
    ui->lineEdit_13->setReadOnly(1);
    ui->lineEdit_14->setReadOnly(1);
    ui->lineEdit_15->setReadOnly(1);
    ui->lineEdit_16->setReadOnly(1);
    ui->lineEdit_17->setReadOnly(1);
    // ui->PathlineEdit->setReadOnly(1);

    // 移动距离
    ui->distanceComb->setCurrentIndex(0);
    ui->InfoTable->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    // 居中
    ui->InfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->InfoTable->horizontalHeader()->setStyleSheet( "QHeaderView::section{background:rgb(2,20,130);color: white;}"))
    ui->InfoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ButtonDisable();
}

// 风压饼状图
void ClimbotWin::Panelinit() {
    panel1=new panel(ui->panel1);
    panel2=new panel(ui->panel2);
    panel3=new panel(ui->panel3);

    panel1->setTitle( "风腔1"))
    panel2->setTitle( "风腔2"))
    panel3->setTitle( "风腔3"))
}


void ClimbotWin::DataviewInit() {
    // 光滑曲线序列
    seriesLine = new QSplineSeries();
    seriesLine1 = new QSplineSeries();
    seriesLine2 = new QSplineSeries();
    // 平面图散点数据分配空间
    series0 = new QScatterSeries();
    series1 = new QScatterSeries();
    series2 = new QScatterSeries();
    /*
    // 三维图点的数据分配空间
     graph3D = new Q3DScatter();
     graphContainer = QWidget::createWindowContainer(graph3D); // Q3DBars继承自QWindow，必须如此创建
     QScatterDataProxy *proxy = new QScatterDataProxy(); // 数据代理
     series_3D = new QScatter3DSeries(proxy);  // 创建序列，问题的关键

     QHBoxLayout *hlayout=new QHBoxLayout();
     hlayout->addWidget(graphContainer,2);
     ui->fm_3D->setLayout(hlayout);
     */
    // 信号与槽，创建定时器
    timer_t = new QTimer(this);
    /*
     connect(timer_t,SIGNAL(timeout()),this,SLOT(BuildGraph3D()));
     connect(timer_t,SIGNAL(timeout()),this,SLOT(RemoveSeries));
     connect(timer_t,SIGNAL(timeout()),this,SLOT(buildScatterChart()));
     */
}

void ClimbotWin::ButtonEnable() {
    ui->cwBtn->setEnabled(1);
    ui->ccwBtn->setEnabled(1);
    ui->distanceComb->setEnabled(1);
}

void ClimbotWin::ButtonDisable() {

    ui->cwBtn->setEnabled(0);
    ui->ccwBtn->setEnabled(0);
    ui->distanceComb->setEnabled(0);
}

// 操作按钮
void ClimbotWin::on_ConnectBtn_clicked() {
    if (!file- > open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() <<  "Open failed." << Qt::endll
        return;
    }

    tcpSocket = nullptr;
    tcpSocket = new QTcpSocket(this);

    // tcp套接字建立连接成功，显示成功建立信息
    connect(tcpSocket, &QTcpSocket::connected,
            [=]() {
                UpdateInfo("Normal", "Connect to Tcp Server");
                qDebug()<<"Connect to Tcp Server";
            });

    connect(tcpSocket, &QTcpSocket::readyRead,this,&ClimbotWin::UpdateFanData);

    // 从setting.json文件读取服务器IP和端口号
    QString ip;
    quint16 port = 0;
    ConRbt->GetServerIP_Port(ip, port);

    // 主动建立tcp连接
    tcpSocket->connectToHost(QHostAddress(ip), port);

    // 显示连接信息
    UpdateInfo("Normal","Connect Server,IP:Port:"+ip+":"+QString::number(port));
    UpdateInfo("Normal","Connect OptiTrick,IP:Port:"+ConRbt->GetOptiTrackIP_Port());
    UpdateInfo("Normal","3D&2D display is turned on");
    file->write("Connect successfully!\n");
    ButtonEnable();
    timer_t->start(500);
    /*
    // 风腔负压值的显示
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     QString start_str = QString("manual\t0.0\t0.0\t0.0\t%1\t%2\t%3\r\n").arg(fan_1).arg(fan_2).arg(fan_3);
     tcpSocket->write(start_str.toUtf8());
     */
    UpdateInfo("Normal","The polish mission is started");
    file->write("The polish mission is started\n");
}


// 发送轨迹文件
void ClimbotWin::on_OpenFileBtn_clicked() {
    /*
     * 初步打开文件框
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*)"));
    ui->PathlineEdit->setText(fileName);
    if(ui->PathlineEdit->text()!="")
    {
        UpdateInfo("Normal","File loaded successful");
    }
    else
    {
        UpdateInfo("Normal","Failed to load file");
    }
    */

    // 下拉框
    if ((ui->fileComboBox->currentIndex()) == 0) {
        QString file_str = QString("file\tBowTrajecory.txt\t");
        tcpSocket->write(file_str.toUtf8());
        file->write(file_str.toUtf8());
        UpdateInfo("Normal", "BowTrajecory");
    }
    if ((ui->fileComboBox->currentIndex()) == 1) {
        QString file_str = QString("file\tMouthTrajecory.txt\t");
        tcpSocket->write(file_str.toUtf8());
        file->write(file_str.toUtf8());
        UpdateInfo("Normal", "MouthTrajecory");
    }
    if ((ui->fileComboBox->currentIndex()) == 2) {
        QString file_str = QString("file\tCircularTrajecory.txt\t");
        tcpSocket->write(file_str.toUtf8());
        file->write(file_str.toUtf8());
        UpdateInfo("Normal", "CircularTrajecory");
    }

}

// 开始键
void ClimbotWin::on_StartBtn_clicked() {
    /*
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     QString path_following_str = QString("path_follow\t0.0\t0.0\t0.0\t%1\t%2\t%3\r\n").arg(fan_1).arg(fan_2).arg(fan_3);
     tcpSocket->write(path_following_str.toUtf8());
     */
    UpdateInfo("Nomal", "The polish mission is path following");
    file->write("The polish mission is path following\n");
}

// 终止键
void ClimbotWin::on_FinishBtn_clicked() {
    QString pause_str = QString("stop\t\r\n");
    tcpSocket->write(pause_str.toUtf8());
    UpdateInfo("Normal","stop");
    /*
    // 断开与服务器连接
    tcpSocket->write("stop\r\n", 7);
    tcpSocket->disconnectFromHost();
    UpdateInfo("Normal","The polish mission is stopped");
    file->write("Normal The polish mission is stopped\n");
    file->close();
    timer_t->stop();
    */
}

// 风机开关按钮
void ClimbotWin::on_EngineStartBtn_clicked() {
     QString up_str = QString("fans\t\r\n");
     tcpSocket->write(up_str.toUtf8());
     file->write(up_str.toUtf8());
     UpdateInfo("Normal", "fans");
}


void ClimbotWin::on_EngineStopBtn_clicked() {
      QString up_str = QString("stopF\t\r\n");
      tcpSocket->write(up_str.toUtf8());
      file->write(up_str.toUtf8());
      UpdateInfo("Normal", "stopF");
}

// 打磨头开关按钮
void ClimbotWin::on_pushButton_10_clicked() {
    QString Process_str = QString("plsStart\t\r\n");
    tcpSocket->write(Process_str.toUtf8());
    file->write(Process_str.toUtf8());
    UpdateInfo("Normal","startProcessing");
}

void ClimbotWin::on_pushButton_11_clicked() {
    QString Process_str = QString("plsStop\t\r\n");
    tcpSocket->write(Process_str.toUtf8());
    file->write(Process_str.toUtf8());
    UpdateInfo("Normal","stopProcessing");
}

// 顺时针移动
void ClimbotWin::on_cwBtn_clicked() {
    /*
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     ang_vel = ui->lineEdit_AngVel->text().toDouble();// 旋转角速度
     */
    int value = ui->comboBox_rotate->currentText().toInt();
    QString clockwise_str;
    clockwise_str =  QString("negaRotate\t%1\t").arg(value);
    tcpSocket->write(clockwise_str.toUtf8());
    file->write(clockwise_str.toUtf8());
    QString ans = "clockwise: " + QString::number(value) + "°";
    UpdateInfo("Normal", ans);
}

// 逆时针移动
void ClimbotWin::on_ccwBtn_clicked() {
    /*
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     ang_vel = ui->lineEdit_AngVel->text().toDouble();// 旋转角速度
     */
    int value = ui->comboBox_rotate->currentText().toInt();
    QString counterclockwise_str;
    counterclockwise_str = QString("posiRotate\t%1\t").arg(value);
    tcpSocket->write(counterclockwise_str.toUtf8());
    file->write(counterclockwise_str.toUtf8());
    QString ans = "counterclockwise: " + QString::number(value) + "°";
    UpdateInfo("Normal", ans);
}

// 设置风腔压力函数
void ClimbotWin::on_pushButton_4_clicked() {
    QString str = QString("set_fan\t%1\t%2\t%3\t\r\n").arg(ui->comboBox_2->currentText()).arg(ui->comboBox_3->currentText()).arg(ui->comboBox_4->currentText());
    tcpSocket->write(str.toUtf8());
    file->write(str.toUtf8());
    UpdateInfo("Normal", "Fan_pre_updated");
}

// 是否进行键盘控制
void ClimbotWin::on_pushButton_2_clicked() {
    if (control == 0) {
        ui->pushButton_2->setText("冻结键盘");
        control = 1;
        this->grabKeyboard();
    } else {
        ui->pushButton_2->setText("激活键盘");
        control = 0;
        this->releaseKeyboard();
    }
}

// 键盘控制上下左右位移
void ClimbotWin::keyPressEvent(QKeyEvent *ev) {
    switch(ev->key()) {
        case Qt::Key_W: {
            if(control) {
                QString up_str = QString("increment\t%1\t%2\t\r\n").arg(0).arg((ui->distanceComb->currentText().toFloat())/1000);
                tcpSocket->write(up_str.toUtf8());
                file->write(up_str.toUtf8());
                UpdateInfo("Normal", "Up");
            }
            break;
        }
        case Qt::Key_A: {
            if(control) {
                QString up_str = QString("increment\t%1\t%2\t\r\n").arg(-(ui->distanceComb->currentText().toFloat())/1000).arg(0);
                tcpSocket->write(up_str.toUtf8());
                file->write(up_str.toUtf8());
                UpdateInfo("Normal", "Left");
            }
                break;
        }
        case Qt::Key_S: {
            if(control) {
                QString up_str = QString("increment\t%1\t%2\t\r\n").arg(0).arg(-(ui->distanceComb->currentText().toFloat())/1000);
                tcpSocket->write(up_str.toUtf8());
                file->write(up_str.toUtf8());
                UpdateInfo("Normal", "Down");
            }
                break;
        }
        case Qt::Key_D: {
            if(control) {
                QString up_str = QString("increment\t%1\t%2\t\r\n").arg((ui->distanceComb->currentText().toFloat())/1000).arg(0);
                tcpSocket->write(up_str.toUtf8());
                file->write(up_str.toUtf8());
                UpdateInfo("Normal", "Right");
            }
            break;
        }
        case Qt::Key_Q: {
            if(control) {
                QString up_str = QString("increment\t%1\t%2\t\r\n").arg(-(ui->distanceComb->currentText().toFloat())/1414).arg((ui->distanceComb->currentText().toFloat())/1414);
                tcpSocket->write(up_str.toUtf8());
                file->write(up_str.toUtf8());
                UpdateInfo("Normal", "Up & Left");
            }
            break;
        }
        case Qt::Key_E: {
            if(control) {
                QString up_str = QString("increment\t%1\t%2\t\r\n").arg((ui->distanceComb->currentText().toFloat())/1414).arg((ui->distanceComb->currentText().toFloat())/1414);
                tcpSocket->write(up_str.toUtf8());
                file->write(up_str.toUtf8());
                UpdateInfo("Normal", "Up & Right");
            }
            break;
        }
        case Qt::Key_Z: {
            if(control) {
                QString up_str = QString("increment\t%1\t%2\t\r\n").arg(-(ui->distanceComb->currentText().toFloat())/1414).arg(-(ui->distanceComb->currentText().toFloat())/1414);
                tcpSocket->write(up_str.toUtf8());
                file->write(up_str.toUtf8());
                UpdateInfo("Normal", "Down & Left");
            }
            break;
        }
        case Qt::Key_C: {
            if(control) {
                QString up_str = QString("increment\t%1\t%2\t\r\n").arg((ui->distanceComb->currentText().toFloat())/1414).arg(-(ui->distanceComb->currentText().toFloat())/1414);
                tcpSocket->write(up_str.toUtf8());
                file->write(up_str.toUtf8());
                UpdateInfo("Normal", "Down & Right");
            }
            break;
        }
    }
}

// 运动控制
void ClimbotWin::on_pushButton_clicked() {
    if ((ui->comboBox->currentIndex()) == 0) {
        QString up_str = QString("stcorr\t\r\n");
        tcpSocket->write(up_str.toUtf8());
        file->write(up_str.toUtf8());
        UpdateInfo("Normal", "stcorr");
    }
    if ((ui->comboBox->currentIndex()) == 1) {
        QString up_str = QString("motion\t\r\n");
        tcpSocket->write(up_str.toUtf8());
        file->write(up_str.toUtf8());
        UpdateInfo("Normal", "motion");
    }
    if ((ui->comboBox->currentIndex()) == 2) {
        QString up_str = QString("track\t\r\n");
        tcpSocket->write(up_str.toUtf8());
        file->write(up_str.toUtf8());
        UpdateInfo("Normal", "track");
    }
    if ((ui->comboBox->currentIndex()) == 3) {
        QString up_str = QString("absolute\t%1\t%2\t\r\n").arg(ui->lineEdit_3->text().toFloat()).arg(ui->lineEdit_2->text().toFloat());
        tcpSocket->write(up_str.toUtf8());
        file->write(up_str.toUtf8());
        UpdateInfo("Normal", "absolute");
    }
    if ((ui->comboBox->currentIndex()) == 4) {
        QString up_str =QString("splineTrack\t\r\n");
        tcpSocket->write(up_str.toUtf8());
        file->write(up_str.toUtf8());
        UpdateInfo("Normal", "splineTrack");
    }
    if ((ui->comboBox->currentIndex()) == 5) {
        QString up_str =QString("getDeltaYaw\t\r\n");
        tcpSocket->write(up_str.toUtf8());
        file->write(up_str.toUtf8());
        UpdateInfo("Normal", "getDeltaYaw");
    }
}

// 坐标值以及风腔气压值更新槽函数(无延时)
void ClimbotWin::UpdateFanData() {
    QString tcp_data;
    QString pose_data;
    QString fan_data;
    int flag_pose = 0;
    int flag_fan  = 0;
    while(1) {
        tcp_data=QString(tcpSocket->readLine());
        if (tcp_data.size() == 0) {
            break;
        }
        if (tcp_data.right(2) == "\r\n") {
            if (tcp_data.left(4) == "pose") {
                // 返回值含该字符串的最右边的2个字符
                pose_data = tcp_data.left(tcp_data.length()-2);
                pose_data = pose_data.right(pose_data.length()-5);
                flag_pose = 1;
                count_trajectory++;
            } else if (tcp_data.left(3) == "fan") {
                fan_data = tcp_data.left(tcp_data.length()-2);
                fan_data = fan_data.right(fan_data.length()-4);
                flag_fan = 1;
            }
        }
    }
    if(flag_pose == 1) {
        QStringList pose_data_list = pose_data.split("\t");
              // 参数：x,y,z,w,x,y,z
              if (pose_data_list.size() != 7) {
                return;
              }
              QString strx=pose_data_list[0];
              QString stry=pose_data_list[1];
              QString strz=pose_data_list[2];
              ui->lineEdit->setText(strx);
              ui->lineEdit_13->setText(stry);
              ui->lineEdit_14->setText(strz);
              QString quanternion_w = pose_data_list[3];
              QString quanternion_x = pose_data_list[4];
              QString quanternion_y = pose_data_list[5];
              QString quanternion_z = pose_data_list[6];

              // 四元数转欧拉角
              Eigen::Quaterniond quaternion
                      (quanternion_w.toFloat(),quanternion_x.toFloat(),quanternion_y.toFloat(),quanternion_z.toFloat());
              Eigen::Vector3d eulerAngle = quaternion.matrix().eulerAngles(2, 1, 0);
              QString strRoll=QString("%1").arg(eulerAngle[0]);
              QString strPitch=QString("%1").arg(eulerAngle[1]);
              QString strYaw  =QString("%1").arg(eulerAngle[2]);
              ui->lineEdit_15->setText(strRoll);
              ui->lineEdit_16->setText(strPitch);
              ui->lineEdit_17->setText(strYaw);

              robot_x = strx.toFloat();
              robot_y = stry.toFloat();
              robot_z = strz.toFloat();

              angle1  = strRoll.toFloat();
              angle2  = strPitch.toFloat();
              angle3  = strYaw.toFloat();

              quanternion_W = quanternion_w.toFloat();
              quanternion_X = quanternion_x.toFloat();
              quanternion_Y = quanternion_y.toFloat();
              quanternion_Z = quanternion_z.toFloat();

              // 移动和旋转
              dobotModel->move(robot_x,robot_y,robot_z);
              // dobotModel->rotate_(angle3);
              dobotModel->rotate_quanternion(quanternion_X,quanternion_Y,quanternion_Z,quanternion_W);
              // 轨迹显示
              if (isTrajectory == true) {
                  if (count_trajectory > 14) {
                      count_trajectory -= 15;
                      Eigen::Vector3d temp(robot_x,robot_y,robot_z);
                      if (trajectory->isOk(temp)) {
                          trajectory->drawLine(temp);
                          trajectory->pointUpdate(temp);
                      }
                  }
              } else {
                  Eigen::Vector3d temp(robot_x, robot_y, robot_z);
                  trajectory->pointUpdate(temp);
              }
    }
    if (flag_fan == 1) {
        QStringList fan_data_list = fan_data.split("\t");
        if (fan_data_list.size() != 3 ) {
            return;
        }
        panel1->setValue(fan_data_list[0].toDouble());
        panel2->setValue(fan_data_list[1].toDouble());
        panel3->setValue(fan_data_list[2].toDouble());
        fan_data = "Fan pressure:["+fan_data_list[0]+"\t"+fan_data_list[1]+"\t"+fan_data_list[2]+"]\n";
        file->write(fan_data.toUtf8());
    } else {
        return;
    }

    /*
     * 有延时的版本：
    QString tcp_data = QString(tcpSocket->readLine());
    if(tcp_data.right(2)=="\r\n")
    {

        if(tcp_data.left(4)=="pose")// 返回值含该字符串的最右边的2个字符
        {
            QString pose_data = tcp_data.left(tcp_data.length()-2);
            pose_data = pose_data.right(pose_data.length()-5);
            QStringList pose_data_list = pose_data.split("\t");
            if(pose_data_list.size() != 3 )
            {
                return;
            }
            QString strx=pose_data_list[0];
            QString stry=pose_data_list[1];
            QString stryaw=pose_data_list[2];
            ui->lineEdit->setText(strx);
            ui->lineEdit_13->setText(stry);
            ui->lineEdit_17->setText(stryaw);
        }
        else if(tcp_data.left(3)=="fan")
        {
            QString fan_data = tcp_data.left(tcp_data.length()-2);
            fan_data = fan_data.right(fan_data.length()-4);
            QStringList fan_data_list = fan_data.split("\t");
            if(fan_data_list.size() != 3 )
            {
                return;
            }
            panel1->setValue(fan_data_list[0].toDouble());
            panel2->setValue(fan_data_list[1].toDouble());
            panel3->setValue(fan_data_list[2].toDouble());
            fan_data = "Fan pressure:["+fan_data_list[0]+"\t"+fan_data_list[1]+"\t"+fan_data_list[2]+"]\n";
            file->write(fan_data.toUtf8());
        }
    }
    return;
    */
}

// 3D绘图
void ClimbotWin::loadDobotModel() {
    // 创建三维场景窗口
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow;
    // 设置三维场景窗口的背景颜色
    // view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xf5f5dc))); // 浅黄
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xedffff)));    // 浅蓝
    // 创建容器用于存放三维场景窗口
    QWidget *container = QWidget::createWindowContainer(view);
    // 设置容器大小
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(200, 100);
    container->setMaximumSize(screenSize);
    // 添加三维场景
    ui->verticalLayout_2->addWidget(container);
    // 输入层
    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);
    // Dobot实体
    dobotModel = new DobotModel;

    // 照相机实体
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(250.0f, 250.0f, 800.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));// 设置为y轴向上
    cameraEntity->setViewCenter(QVector3D(150.0f, 150.0f, 50.0f));
    // 照相机控制
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(dobotModel);
    camController->setLinearSpeed(50.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(cameraEntity);

    // 点光源
    // 灯光实体
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(dobotModel);
    // 灯光组件
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.8);
    // 向实体添加组件
    lightEntity->addComponent(light);
    // 灯光变换组件
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    // 向实体添加组件
    lightEntity->addComponent(lightTransform);

    // 设置场景的根实体
    view->setRootEntity(dobotModel);
    trajectory = new Trajectory(Qt::red,dobotModel);
}

// 设置轨迹按钮
// 开始显示
void ClimbotWin::on_pushButton_5_clicked() {
    isTrajectory = true;
    UpdateInfo("Normal", "trajectoryRocord_started");
}
// 停止显示
void ClimbotWin::on_pushButton_7_clicked() {
    isTrajectory = false;
    count_trajectory = 0;
    UpdateInfo("Normal", "trajectoryRocord_stopped");
}
// 清空轨迹
void ClimbotWin::on_pushButton_9_clicked() {
    trajectory->clearTrajectory();
    UpdateInfo("Normal", "trajectoryRocord_cleared");
}



/**
 * 废键：
 // 暂停键
 void ClimbotWin::on_StopBtn_clicked()
 {
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     QString pause_str = QString("manual\t0.0\t0.0\t0.0\t%1\t%2\t%3\r\n").arg(fan_1).arg(fan_2).arg(fan_3);
     tcpSocket->write(pause_str.toUtf8());
     UpdateInfo("Normal","The polish mission is paused");
     file->write("The polish mission is paused\n");
 }
 // 急停键
 void ClimbotWin::on_EMCBtn_clicked()
 {
     // 断开与服务器连接
     tcpSocket->write("emergency\r\n", 12);
     tcpSocket->disconnectFromHost();
     file->write("Emergency Stop is pressed!\n");
     file->close();
     timer_t->stop();
     UpdateInfo("Normal","Emergency Stop is pressed!");
 }
 // 刷新设置文件
 void ClimbotWin::on_LoadSettingBtn_clicked()
 {
     if(ConRbt->RefreshSettingData())
         UpdateInfo("Normal","setting file is refreshed");
 }
 // 上下左右键
 void ClimbotWin::on_UpBtn_clicked()
 {
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     distance = ui->distanceComb->currentText().toDouble();
     QString up_str = QString("increment\t%1\t%2\t\r\n").arg(0).arg((ui->distanceComb->currentText().toInt())/1000);
     tcpSocket->write(up_str.toUtf8());
     file->write(up_str.toUtf8());
     UpdateInfo("Normal", "Up");
 }
 void ClimbotWin::on_LeftBtn_clicked()
 {
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     distance = ui->distanceComb->currentText().toDouble();
     QString left_str =
             QString("params x -0.2\t%1\t0.0\t0.0\t%2\t%3\t%4\r\n").arg(-distance*1e-3).arg(fan_1).arg(fan_2).arg(fan_3);
     tcpSocket->write(left_str.toUtf8());
     file->write(left_str.toUtf8());
     UpdateInfo("Normal", "Left");
 }
 void ClimbotWin::on_RightBtn_clicked()
 {
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     distance = ui->distanceComb->currentText().toDouble();
     QString right_str =
             QString("params x 0.2\t%1\t0.0\t0.0\t%2\t%3\t%4\r\n").arg(distance*1e-3).arg(fan_1).arg(fan_2).arg(fan_3);
     tcpSocket->write(right_str.toUtf8());
     file->write(right_str.toUtf8());
     UpdateInfo("Normal", "Right");
 }
 void ClimbotWin::on_DownBtn_clicked()
 {
     fan_1 = ui->lineEdit_Fan->text().toInt();
     fan_2 = ui->lineEdit_Fan_2->text().toInt();
     fan_3 = ui->lineEdit_Fan_3->text().toInt();
     distance = ui->distanceComb->currentText().toDouble();
     QString down_str =
             QString("params y -0.2\t0.0\t%1\t0.0\t%2\t%3\t%4\r\n").arg(-distance*1e-3).arg(fan_1).arg(fan_2).arg(fan_3);
     tcpSocket->write(down_str.toUtf8());
     file->write(down_str.toUtf8());
     UpdateInfo("Normal", "Down");
 }
 测试（废）
 void ClimbotWin::timerUpDate()
 {
     QDateTime time = QDateTime::currentDateTime();
        qDebug() << time;
        QString timeStr = time.toString("yyyy-MM-dd dddd hh:mm:ss");
        ui->plainTextEdit->appendPlainText(timeStr);
 }
 void ClimbotWin::timerEvent(QTimerEvent *t)
 {
     QDateTime time = QDateTime::currentDateTime();
         QString timeStr = time.toString("yyyy-MM-dd dddd hh:mm:ss");
         switch (t->timerId())
         {
         case 1:
             ui->plainTextEdit->appendPlainText(timeStr + tr(" timerId = %1").arg(t->timerId()));
             break;
         case 2:
             ui->plainTextEdit->appendPlainText(timeStr + tr(" timerId = %1").arg(t->timerId()));
             break;
         case 3:
             ui->plainTextEdit->appendPlainText(timeStr + tr(" timerId = %1").arg(t->timerId()));
             break;
         default:
             ui->plainTextEdit->appendPlainText(timeStr + tr(" timerId = %1").arg(t->timerId()));
             break;
         }
 }
 // 测试（新）
 void ClimbotWin::onTimeOut()
 {
     static int value =0;
     robot_x+=10;
     robot_y+=10;
     dobotModel->move_(robot_x,robot_y);
 }
*/



