#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dpll.h"
#include "sudoku.h"
#include <QList>
#include <qvalidator.h>
#include <QFileDialog>
#include <QTextCodec>
#include <qdebug.h>
#include <iomanip>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    int satOrSudoku = 0;            // SAT或者SUDOKU模块二选一解锁
    int difficultyChoice = 0;       // 随机数独难度选择
    bool solveButtonIsOK = false;   // SUDOKU已经解决
    int satStepOption = 0;          // SAT步骤（1：求解；2：检验正确性；3：保存文件
    int optimizationChoice = 0;     // 优化方案选择
    int solut = 0;                  // solut记录CNF公式是否有解，有解为1，无解为0
    float duration = 0.00;          // 记录SAT求解时间
    QString importFileName ="";     // sudoku导入文件名称
    QString importFileNameSAT = ""; // sat导入文件名称
    int lockAll = 0;                // 总解锁键
    ~MainWindow();

    // sudoku模块按钮
    void initSudoku();
    void submitSudoku();
    void SolveSudoku();
    void CheckSudoku();
    void ClearBoard();
    void ImportFile();
    status SolveSudokuGame(void);

private slots:

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_toolButton_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
