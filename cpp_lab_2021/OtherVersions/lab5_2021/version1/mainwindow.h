#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "busMap.h"
#include "dialog.h"
#include <QMouseEvent>
#include <string>
#include <QPoint>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    busMap *bp;
    bool isClicked;
    int startPointIndex=0,endPointIndex=0;
    int* ans;
    int timerId=0;
    QPoint startPos,endPos;

public:
    void findPointByName();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
