#include "busdialog.h"
#include "ui_BusDialog.h"

BusDialog::BusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BusDialog) {
    ui->setupUi(this);
}

BusDialog::~BusDialog() {
    delete ui;
}

void BusDialog::on_pushButton_clicked() {
    point_name_ = ui->lineEdit->text();
    close();
}
