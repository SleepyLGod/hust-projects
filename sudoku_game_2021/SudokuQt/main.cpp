#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Sudoku Game By Mr.Lu");
    w.setWindowIcon(QIcon(":/new/src/image/hust.png"));
    w.setFixedSize(1057,740);
    w.show();
    return a.exec();
}
