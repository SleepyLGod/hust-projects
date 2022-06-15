#ifndef DIALOG_H
#define DIALOG_H
#include <QString>
#include <QDialog>
#include <QPushButton>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    QString pointName;
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
