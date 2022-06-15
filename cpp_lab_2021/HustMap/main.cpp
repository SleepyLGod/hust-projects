#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QString qss;
    QFile qssFile(":/myQss.qss");
    qssFile.open(QFile::ReadOnly);
    if (qssFile.isOpen()) {
      qss = QLatin1String(qssFile.readAll());
      qApp->setStyleSheet(qss);
      qssFile.close();
    }
    MainWindow w;
    w.setWindowTitle("HustMap_V1.0");
    w.setWindowIcon(QIcon(":/image/hust.png"));
    w.show();
    return a.exec();
}
