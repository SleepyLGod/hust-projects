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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->checkBox_transfers->setChecked(true);
    move(30,20);
    start_pos_.setX(0);
    start_pos_.setY(0);
    end_pos_.setX(0);
    end_pos_.setY(0);
    is_cliked_ = false;
    bp_ = new BusMap("./res/stops.txt",
                     "./res/lines.txt",
                     "./res/Organization.txt");
    connect(ui->action_Ctrl_R, &QAction::triggered, this, &MainWindow::findPointByName);
}

MainWindow::~MainWindow() {
    delete ui;
    delete bp_;
}

void MainWindow::paintEvent(QPaintEvent *) {
    // map
    ui->frame->setFixedHeight(820);
    ui->frame->setFixedWidth(1676);
    QRect maprect = ui->frame->frameRect();
    maprect.translate(ui->frame->pos());
    QImage mapImage(":/res/hustMap.bmp");
    QPainter mapPainter(this);
    QPen mapPen;
    mapPainter.drawImage(maprect,mapImage);

    // stop points
    QRectF busStopsRect;
    mapPainter.setBrush(QColor(0,0,0));
    for (int i = 1; i <= bp_->get_bus_stop_cnt_(); ++i) {
        MapPoint *_p = bp_->get_bus_stops_()[i];
        busStopsRect.setTop(_p->get_point_pos().second + 6);
        busStopsRect.setBottom(_p->get_point_pos().second - 6);
        busStopsRect.setLeft(_p->get_point_pos().first - 6);
        busStopsRect.setRight(_p->get_point_pos().first + 6);
        mapPainter.drawEllipse(busStopsRect);
    }

    // start and end point
    if (start_pos_.x() != 0) {
        mapPen.setWidth(2);
        mapPen.setColor(Qt::blue);
        mapPainter.setBrush(Qt::blue);
        mapPainter.setPen(mapPen);
        busStopsRect.setTop(start_pos_.y() + 6);
        busStopsRect.setBottom(start_pos_.y() - 6);
        busStopsRect.setLeft(start_pos_.x() - 6);
        busStopsRect.setRight(start_pos_.x() + 6);
        mapPainter.drawEllipse(busStopsRect);
    }
    if (end_pos_.y() != 0) {
        mapPen.setColor(Qt::green);
        mapPainter.setBrush(Qt::green);
        mapPainter.setPen(mapPen);
        busStopsRect.setTop(end_pos_.y() + 6);
        busStopsRect.setBottom(end_pos_.y() - 6);
        busStopsRect.setLeft(end_pos_.x() - 6);
        busStopsRect.setRight(end_pos_.x() + 6);
        mapPainter.drawEllipse(busStopsRect);
    }

    // draw bus lines
    mapPainter.setBrush(Qt::NoBrush);
    mapPen.setWidth(4);
    mapPen.setColor(Qt::darkCyan);
    mapPen.setStyle(Qt::DotLine);
    mapPainter.setPen(mapPen);
    for (int i = 1; i <= bp_->get_bus_line_cnt_(); ++i) {
        for (int j = 1; j < bp_->get_each_bus_line_num_()[i]; ++j) {
            MapPoint *_p1 = bp_->get_bus_stops_()[bp_->get_bus_lines_()[i][j]];
            MapPoint *_p2 = bp_->get_bus_stops_()[bp_->get_bus_lines_()[i][j + 1]];
            mapPainter.drawLine(_p1->get_point_pos().first, _p1->get_point_pos().second, _p2->get_point_pos().first, _p2->get_point_pos().second);
        }
    }

    // path
    int temp = end_point_index_;
    if (!ans_ || temp == 0) {
        return;
    }

    mapPen.setWidth(3);
    mapPen.setColor(Qt::red);
    mapPen.setStyle(Qt::SolidLine);
    mapPainter.setPen(mapPen);
    mapPainter.setBrush(Qt::NoBrush);
    mapPainter.drawLine(end_pos_.x(),end_pos_.y(),bp_->get_bus_stops_()[temp]->get_point_pos().first,
                        bp_->get_bus_stops_()[temp]->get_point_pos().second);
    while (ans_[temp]) {
        mapPainter.drawLine(bp_->get_bus_stops_()[temp]->get_point_pos().first,
                            bp_->get_bus_stops_()[temp]->get_point_pos().second,
                            bp_->get_bus_stops_()[ans_[temp]]->get_point_pos().first,
                            bp_->get_bus_stops_()[ans_[temp]]->get_point_pos().second);
        temp = ans_[temp];
    }
    mapPainter.drawLine(start_pos_.x(),start_pos_.y(),bp_->get_bus_stops_()[temp]->get_point_pos().first,
                        bp_->get_bus_stops_()[temp]->get_point_pos().second);
}

int StringMatchUtil(string a, string b) {
    int cnt = 0;
    for (int i = 0; i < b.length(); i += 3) {
        for (int j = 0; j < a.length(); j += 3) {
            bool flag = true;
            if (i + 2 < b.length() && j + 2 < a.length()) {
                for (int k = 0; k < 3; ++k) {
                    if (a[j + k] != b[i + k]) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                cnt++;
                break;
            }
        }
    }
    return cnt;
}

void MainWindow::timerEvent(QTimerEvent *event) {
    start_point_index_ = 0;
    end_point_index_ = 0;
    start_pos_.setX(0);
    start_pos_.setY(0);
    end_pos_.setX(0);
    end_pos_.setY(0);
    killTimer(timer_id_);
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QPoint mousePoint = event->pos();
    MapPoint mousePointTemp;
    mousePointTemp.set_point_pos_(mousePoint.x(), mousePoint.y());
    double minDistance = 9999999.99;
    for (int i = 1; i <= bp_->get_bus_stop_cnt_(); ++i) {
        double temp=calculateDistance(mousePointTemp, *bp_->get_bus_stops_()[i]);
        if (temp < minDistance) {
            if (!is_cliked_) {
                minDistance = temp;
                start_point_index_ = i;
            } else {
                minDistance = temp;
                end_point_index_ = i;
            }
        }
    }
    if (!is_cliked_) {
        is_cliked_ = true;
        start_pos_ = event->pos();
        end_pos_.setX(0);
        end_pos_.setY(0);
        repaint(ui->centralwidget->contentsRect());
        killTimer(timer_id_);
    } else {
        end_pos_ = event->pos();
        if (ui->checkBox_nearest->isChecked()) {
            ans_ = bp_->findDirectPath(start_point_index_, end_point_index_);
        } else {
            ans_ = bp_->findEveryPath(start_point_index_, end_point_index_);
        }
        repaint(ui->centralwidget->contentsRect());
        timer_id_ = startTimer(5000);
        start_point_index_ = 0;
        end_point_index_ = 0;
        start_pos_.setX(0);
        start_pos_.setY(0);
        end_pos_.setX(0);
        end_pos_.setY(0);
        is_cliked_ = false;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_R)
        findPointByName();
}

void MainWindow::findPointByName() {
    BusDialog *findPointDialog;
    findPointDialog = new BusDialog(this);
    findPointDialog->show();
    findPointDialog->exec();
    string pointName = findPointDialog->point_name_.toStdString();
    if (pointName.empty()) {
        delete findPointDialog;
        return;
    } else {
        if (!is_cliked_) {
            int maxCnt = 0;
            int ansIndex = 0;
            for (int i = 1; i <= bp_->get_organizations_cnt_(); i++) {
                if (StringMatchUtil(bp_->get_organization_names_()[i], pointName) > maxCnt) {
                    maxCnt = StringMatchUtil(bp_->get_organization_names_()[i], pointName);
                    ansIndex = i;
                }
            }
            if (ansIndex == 0) {
                delete findPointDialog;
                QMessageBox tempMessageBox(QMessageBox::Critical,"查找失败", "未查找到地点!", QMessageBox::Ok,this);
                tempMessageBox.exec();
                return;
            }
            killTimer(timer_id_);
            is_cliked_ = true;
            start_pos_.setX(bp_->get_organization_pos_()[ansIndex].first);
            start_pos_.setY(bp_->get_organization_pos_()[ansIndex].second);
            MapPoint startPointTemp;
            startPointTemp.set_point_pos_(start_pos_.x(),start_pos_.y());
            double minDistance = 9999999.99;
            for (int i = 1; i <= bp_->get_bus_stop_cnt_(); ++i) {
                double temp = calculateDistance(startPointTemp, *bp_->get_bus_stops_()[i]);
                if (temp < minDistance) {
                    minDistance = temp;
                    start_point_index_ = i;
                }
            }
            repaint(ui->centralwidget->contentsRect());
        } else {
            int maxCnt = 0;
            int ansIndex = 0;
            for (int i = 1; i <= bp_->get_organizations_cnt_(); ++i) {
                if (StringMatchUtil(bp_->get_organization_names_()[i], pointName) > maxCnt) {
                    maxCnt = StringMatchUtil(bp_->get_organization_names_()[i],pointName);
                    ansIndex = i;
                }
            }
            if (ansIndex == 0) {
                delete findPointDialog;
                QMessageBox tempMessageBox(QMessageBox::Critical,"查找失败", "未查找到地点!", QMessageBox::Ok,this);
                tempMessageBox.exec();
                return;
            }
            end_pos_.setX(bp_->get_organization_pos_()[ansIndex].first);
            end_pos_.setY(bp_->get_organization_pos_()[ansIndex].second);
            MapPoint endPointTemp;
            endPointTemp.set_point_pos_(end_pos_.x(),end_pos_.y());
            double minDistance = 9999999.99;
            for (int i = 1; i <= bp_->get_bus_stop_cnt_(); ++i) {
                double temp=calculateDistance(endPointTemp, *bp_->get_bus_stops_()[i]);
                if (temp < minDistance) {
                    minDistance = temp;
                    end_point_index_ = i;
                }
            }
            if (ui->checkBox_nearest->isChecked()) {
                ans_ = bp_->findDirectPath(start_point_index_, end_point_index_);
            } else {
                ans_ = bp_->findEveryPath(start_point_index_, end_point_index_);
            }
            repaint(ui->centralwidget->contentsRect());
            timer_id_ = startTimer(5000);
            start_point_index_ = 0;
            end_point_index_ = 0;
            is_cliked_ = false;
        }
    }
    delete findPointDialog;
}


void MainWindow::on_checkBox_nearest_stateChanged(int arg1) {
    if (ui->checkBox_nearest->isChecked()) {
        ui->checkBox_transfers->setChecked(false);
    } else {
        ui->checkBox_transfers->setChecked(true);
    }
}


void MainWindow::on_checkBox_transfers_stateChanged(int arg1) {
    if (ui->checkBox_transfers->isChecked()) {
        ui->checkBox_nearest->setChecked(false);
    } else {
        ui->checkBox_nearest->setChecked(true);
    }
}
