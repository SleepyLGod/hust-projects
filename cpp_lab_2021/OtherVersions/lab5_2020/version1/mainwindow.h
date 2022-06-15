#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QDockWidget>
#include <search.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPalette palette;//创建一个调色板对象
    QToolButton *MyButton[25];
    search Search;


private slots:


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
