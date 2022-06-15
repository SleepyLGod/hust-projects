#ifndef BUSDIALOG_H
#define BUSDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <iostream>

namespace Ui {
class BusDialog;
}

class BusDialog : public QDialog
{
    Q_OBJECT

public:
    QString point_name_;
    explicit BusDialog(QWidget *parent = nullptr);
    ~BusDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BusDialog *ui;
};

#endif // BUSDIALOG_H
