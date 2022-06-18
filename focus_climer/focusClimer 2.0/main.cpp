#include "ClimbotWin.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ClimbotWin w;

    //窗口标题以及图标
    w.setWindowIcon(QIcon(":/png/image/focus.png"));
    w.setWindowTitle("FocusClimer_V1.0");

    QString qss;
    QFile qssFile(":/myqss.qss");
    qssFile.open(QFile::ReadOnly);
    if (qssFile.isOpen()) {
      qss = QLatin1String(qssFile.readAll());
      qApp->setStyleSheet(qss);
      qssFile.close();
    }

    //w.showMaximized();
    w.show();
    w.resize(1500,800);
    return a.exec();
}
