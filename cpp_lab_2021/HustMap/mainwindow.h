#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMouseEvent>
#include <string>
#include <QPoint>
#include "BusMap.h"
#include "mappoint.h"
#include "mapedge.h"
#include "busdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    BusMap *bp_;
    bool is_cliked_;
    int start_point_index_ = 0;
    int end_point_index_ = 0;
    int* ans_;
    int timer_id_ = 0;
    // drawers about the line:
    QPoint start_pos_;
    QPoint end_pos_;

public:
    void findPointByName();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_nearest_stateChanged(int arg1);

    void on_checkBox_transfers_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H
