#include "mainwindow.h"
#include "ui_mainwindow.h"

extern ArgueValue *ValueList;
extern Root *r;
extern int *Frequency;
extern QString answerCheckInfo;

float duration = 0;
int *stack;
int instacksize;
mainstack *stackmain;
char filename[1000];
int sudoku_table[9][9]; // 定义全局变量int类型二维数组存储数独盘
int users_sudoku[9][9]; // 存储输出的含空格数独问题格局

// 构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    // 定义一些按钮
    QPushButton  *initialButton = this->findChild<QPushButton *>(QString("pushButton"));
    QPushButton  *SubmitButton = this->findChild<QPushButton *>(QString("pushButton_2"));
    QPushButton  *SolveButton = this->findChild<QPushButton *>(QString("pushButton_3"));
    QPushButton  *ClearButton = this->findChild<QPushButton *>(QString("pushButton_4"));
    QPushButton  *ImportButtom = this->findChild<QPushButton *>(QString("pushButton_5"));
    connect(initialButton, &QPushButton::clicked, this, &MainWindow::initSudoku);
    connect(SolveButton, &QPushButton::clicked, this, &MainWindow::SolveSudoku);
    connect(SubmitButton, &QPushButton::clicked, this, &MainWindow::submitSudoku);
    connect(ClearButton, &QPushButton::clicked, this, &MainWindow::ClearBoard);
    connect(ImportButtom, &QPushButton::clicked, this, &MainWindow::ImportFile);
    // 初始化数独盘
    QRegExp regExp ("[1-9]");
    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9; j ++) {
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            box->setValidator(new QRegExpValidator(regExp, this));
        }
    }
    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9; j ++) {
            QLineEdit * box =
                    this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
                box->setEnabled(false);
        }
    }
    // 初始化所有按钮和文本框（锁）
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);
    ui->radioButton_3->setEnabled(false);
    ui->radioButton_4->setEnabled(false);
    ui->radioButton_5->setEnabled(false);
    ui->radioButton_6->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->plainTextEdit->setEnabled(false);
    ui->plainTextEdit_2->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
    ui->toolButton->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->toolButton_2->setEnabled(false);
    ui->pushButton_13->setEnabled(false);
    // 初始化解锁按钮
    lockAll = 0;
}

// 退出
MainWindow::~MainWindow()
{
    delete ui;
}

// 开启游戏按钮
void MainWindow::on_pushButton_12_clicked()
{
    lockAll++;
    if(lockAll%2) {
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    } else {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->radioButton->setEnabled(false);
        ui->radioButton_2->setEnabled(false);
        ui->radioButton_3->setEnabled(false);
        ui->radioButton_4->setEnabled(false);
        ui->radioButton_5->setEnabled(false);
        ui->radioButton_6->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->plainTextEdit->setEnabled(false);
        ui->plainTextEdit_2->setEnabled(false);
        ui->pushButton_11->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_9->setEnabled(false);
        ui->toolButton->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->toolButton_2->setEnabled(false);
        ui->pushButton_13->setEnabled(false);
    }
}

// 解锁 SUDOKU 模块
void MainWindow::on_pushButton_6_clicked()
{
    satOrSudoku = 1;
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->radioButton->setEnabled(true);
    ui->radioButton_2->setEnabled(true);
    ui->radioButton_3->setEnabled(true);

    ui->pushButton_13->setEnabled(false);
    ui->radioButton_4->setEnabled(false);
    ui->radioButton_5->setEnabled(false);
    ui->radioButton_6->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->plainTextEdit->setEnabled(false);
    ui->plainTextEdit_2->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
    ui->toolButton->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->toolButton_2->setEnabled(false);

    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9; j ++) {
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
                box->setEnabled(true);
        }
    }
}

// 解锁 SAT 模块
void MainWindow::on_pushButton_7_clicked()
{
    satOrSudoku = 2;
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);
    ui->radioButton_3->setEnabled(false);

    ui->radioButton_4->setEnabled(true);
    ui->radioButton_5->setEnabled(true);
    ui->radioButton_6->setEnabled(true);
    ui->lineEdit_3->setEnabled(true);
    ui->plainTextEdit->setEnabled(true);
    ui->plainTextEdit_2->setEnabled(true);
    ui->pushButton_11->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_9->setEnabled(true);
    ui->toolButton->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->toolButton_2->setEnabled(true);
    ui->pushButton_13->setEnabled(true);

    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9; j ++) {
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
                box->setEnabled(false);
        }
    }
}

/* Sudoku Solver 模块 */
// 生成随机数独盘
void MainWindow::initSudoku()
{
//    solveButtonIsOK = true;
    QList<QLineEdit *> singleBoxes = this->findChildren<QLineEdit *>();
    this->ClearBoard();
    int solut = CreateSudoku();       // 生成基础数独终盘对应变元真值表
    if (solut) {
        SudokuComplete();
        CNFSudokuTableTransform();    // 将求解的变元真值表转换为二维数组数独终盘
        SudokuExchange();             // 生成交换元素增加随机性后的数独终盘
        switch (difficultyChoice) {
            case 1:
                DigHole(30);
                break;
            case 2:
                DigHole(50);
                break;
            case 3:
                DigHole(64);
                break;
            default:
                printf("输入出错！\n");
                break;
        }
    }
    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9; j ++) {
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            box->setText("");
            if (users_sudoku[i][j]) {
                box->setEnabled(false);
                box->setText(QString::number(users_sudoku[i][j]));
            } else {
                box->setEnabled(true);
            }
        }
    }
}

// 生成简单难度随机数独
void MainWindow::on_radioButton_clicked()
{
    difficultyChoice = 1;
}

// 生成中等难度随机数独
void MainWindow::on_radioButton_2_clicked()
{
    difficultyChoice = 2;
}

// 生成高等难度随机数独
void MainWindow::on_radioButton_3_clicked()
{
    difficultyChoice = 3;
}

// 生成答案
void MainWindow::SolveSudoku(){
//    if(solveButtonIsOK = true)
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            if (sudoku_table[i][j]){
                box->setText(QString::number(sudoku_table[i][j]));
            }
        }
    }
//    solveButtonIsOK = false;
}

// 提交解答与判断正误
void MainWindow::submitSudoku(){
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            if (sudoku_table[i][j] && box->isEnabled()){
                int temp = box->text().toInt();
                if (sudoku_table[i][j] == temp)
                    box->setStyleSheet("QLineEdit{border: 1px solid green;}");
                else
                    box->setStyleSheet("QLineEdit{border: 1px solid red;}");
            }else {
                box->setStyleSheet("");
            }
        }
    }
//    solveButtonIsOK = true;
}

// 清空解答
void MainWindow::ClearBoard(){
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            if (box->isEnabled()){
                box->setText("");
            }
            box->setStyleSheet("");
        }
    }
//    solveButtonIsOK = true;
}

// 导入文件按钮
void MainWindow::ImportFile() {
    memset(&sudoku_table,0,sizeof (sudoku_table));
    memset(&users_sudoku,0,sizeof (users_sudoku));
    importFileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*)"));
    ui->lineEdit->setText(importFileName);
    this->ClearBoard();
    if(SolveSudokuGame() == OK){
//    solveButtonIsOK = true;
    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9; j ++) {
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            box->setText("");
            if (users_sudoku[i][j]) {
                box->setEnabled(false);
                box->setText(QString::number(users_sudoku[i][j]));
            } else {
                box->setEnabled(true);
            }
        }
    }
  }
   else
   ui->lineEdit->setText(importFileName+QString(" open failed!"));
}

// 求解数独cnf文件并转化为数独终盘形式输出
status MainWindow::SolveSudokuGame(void) {
    FILE *fp;
    char read;
    int i,j,k,x,y,d,cham;
    int exitnum[10];
    /**
    std::string str = importFileName.toStdString();
    const char * filename = str.c_str();
    */
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QByteArray str = importFileName.toLocal8Bit();
    const char *filename = str.data();
    fp=fopen(filename, "r");
    if (fp==NULL) {
        qDebug() << "数独文件打开错误！\n";
        return ERROR;
    }
    for (i=0; i<2; i++) {
        fscanf(fp, "%c",&read);
        while (read!='\n')
            fscanf(fp, "%c",&read);
    }
    /*读取数独文件中的数独问题盘*/
    for (i=0; i<9; i++) {
        j=0;
        fscanf(fp, "%c",&read);
        while (read!='\n') {
            if (read=='.') {
                sudoku_table[i][j]=0;
            }
            else if (read<='9'&&read>='1') {
                sudoku_table[i][j]=(int)(read-'0');
            }
            else j=-1;
            j++;
            fscanf(fp, "%c",&read);
        }
    }
    memcpy(users_sudoku, sudoku_table, sizeof (users_sudoku));
    fclose(fp);
    fp=fopen(filename, "r");
    CreateParadigm(&fp);    // 创建数独文件对应CNF公式邻接链表及变元表

    /*处理数独文件中得到的已知数独信息，建立变元与cell填入值的对应关系*/
    k=1;
    for (i=0; i<9; ++i) {
        for (j=0; j<9; ++j)
            if (sudoku_table[i][j]==0) {
                for (d=0; d<=9; ++d)
                    exitnum[d]=0;
                for (y=0; y<9; ++y) {
                    exitnum[sudoku_table[i][y]]=1;
                }                               // 处理行，记录行中已存在的数
                for (x=0; x<9; ++x) {
                    exitnum[sudoku_table[x][j]]=1;
                }                               // 处理列，记录列中已存在的数
                for (x=(i/3)*3; x<(i/3)*3+3; ++x) {
                    for (y=(j/3)*3; y<(j/3)*3+3; ++y)
                        exitnum[sudoku_table[x][y]]=1;
                }                               // 处理region，记录region中已存在的数
                for (cham=1; cham<=9; ++cham)
                    if (exitnum[cham]==0) {
                        ValueList[k].xyz.x=i;   // 记录该变元对应的数独cell的行数
                        ValueList[k].xyz.y=j;   // 记录该变元对应的数独cell的列数
                        ValueList[k].xyz.z=cham;// 记录该变元对应的数独的填入值
                        ++k;                    // 处理下一变元
                    }
            }
    }
    DPLL1(FindLiteral1(r), 1,1);                // 求解数独文件
    for (k=1; k<=r->litsize; k++) {
        if (ValueList[k].Value==1)
            sudoku_table[ValueList[k].xyz.x][ValueList[k].xyz.y]=ValueList[k].xyz.z;
    }                                           // 将变元表真值信息转换为二维数组的数独信息
    fclose(fp);
    return OK;
}


/* SAT Solver 模块 */
// 开始SAT求解
void MainWindow::on_toolButton_clicked()
{
    int op = 0;                           // 记录选择的操作序号
    int choose = 0;                       // 记录选择的算法序号
    int i = 0;
    clock_t start = 0.00,finish = 0.00;   // 记录DPLL函数调用的起始和终止时间
    importFileNameSAT = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*)")); // 打开文件
    ui->lineEdit_2->setText(importFileNameSAT);
    /**
    std::string str = importFileNameSAT.toStdString();
    const char * satFilename = str.c_str();
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    */
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QByteArray str = importFileNameSAT.toLocal8Bit();
    const char *satFilename = str.data();

    FILE *satOpen;
    satOpen = fopen(satFilename, "r");
    if (satOpen == NULL)
    {
        qDebug() <<"文件打开错误！\n";
        ui->lineEdit_2->setText(QString("文件打开错误!"));
        getchar();getchar();
    }
    if (CreateParadigm(&satOpen) == ERROR)
    {
        // 生成CNF公式数据存储结构
        getchar();getchar();
    }
    int decision = 0;
    decision = OccurTimeCount();    // 预处理CNF公式变元出现次数信息，决定采取的最佳变元选择策略
    solut = 5;
    op = satStepOption;
    QString info,info2,infoTime;
    float timeInterval;
    switch (op)
    {
        case 1:
            if (ValueList[1].IsInit == 1)
            {
                qDebug() <<"已对公式求解！";
                getchar();getchar();
                break;
            }
            choose = optimizationChoice;
            switch (choose)
            {
                case 1:
                    if (decision == 1)
                    {
                        start = clock();
                        solut = DPLL1(FindLiteral1(r),1,1);
                        finish = clock();
                        duration = (float)(finish-start)/1000.0;
                    }
                    else if (decision == 2)
                    {
                        start = clock();
                        solut = DPLL2(FindLiteral2(r),1,1);
                        finish = clock();
                        duration = (float)(finish-start)/1000.0;
                    }
                    else if (decision == 3)
                    {
                        start = clock();
                        solut = DPLL3(FindLiteral3(r),1,1);
                        finish = clock();
                        duration = (float)(finish-start)/1000.0;
                    }
                    else if (decision == 4)
                    {
                        start = clock();
                        solut = DPLL4(FindLiteral4(r),1,1);
                        finish = clock();
                        duration = (float)(finish-start)/1000.0;
                    }
                    break;
                case 2:
                    start = clock();
                    solut = DPLL2(FindLiteral2(r),1,1);
                    finish = clock();
                    duration = (float)(finish-start)/1000.0;
                    break;
                case 3:
                    start = clock();
                    solut = DPLL_Before(r, 1);
                    finish = clock();
                    duration = (float)(finish-start)/1000.0;
                    break;
                default:
                    qDebug() <<"输入错误！\n";
                    break;
            }
            if (solut)
            {
                AnswerComplete();
                for (i = 1; i<= r->litsize; i++)
                {
                    info = QString("变元%1，真值为%2\n").arg(i).arg(ValueList[i].Value);
                    qDebug() << info;
                    info2+=info;
                }
            }
            else
            {
                info2 = QString("该公式无解!\n");
            }
            timeInterval = (double)((finish-start)/1000.000*1000.000);
            infoTime = QString::number(timeInterval, 'f', 9)+QString(" ms");
            info2 = info2.left(info2.length() - 1);
            ui->lineEdit_3->setText(infoTime);
            ui->plainTextEdit->appendPlainText(info2);
            break;
        case 0:
            break;
        default:
            qDebug() <<"输入错误！";
            getchar();getchar();
            break;
    }
//    }
}

// 选择优化算法1
void MainWindow::on_radioButton_4_clicked()
{
    optimizationChoice = 1;
}

// 选择优化算法2
void MainWindow::on_radioButton_5_clicked()
{
    optimizationChoice = 2;
}

// 选择未优化的算法
void MainWindow::on_radioButton_6_clicked()
{
    optimizationChoice = 3;
}

// start按钮，开始游戏
void MainWindow::on_pushButton_11_clicked()
{
    satStepOption = 1;
}

// 检验求解正确性
void MainWindow::on_pushButton_9_clicked()
{
    satStepOption = 2;
    QString info;
        if (solut == 5)
        {
            info = QString("请先求解CNF公式！\n");
            qDebug() <<"请先求解CNF公式！\n";
        }
        QString answerCheckInfo = ParadigmTrabverse(r);
        answerCheckInfo = answerCheckInfo.left(answerCheckInfo.length() - 1);
        ui->plainTextEdit_2->appendPlainText(answerCheckInfo);
        if (AnswerCheck(solut) == OK)
        {
            info = QString("\n公式解析正确！");
            ui->plainTextEdit_2->appendPlainText(info);
            qDebug() <<"公式解析正确！\n";
        } else
        {
            info =QString("\nERROR!");
            ui->plainTextEdit_2->appendPlainText(info);
            qDebug() <<"ERROR！\n";
        }
}

// 保存解文件
void MainWindow::on_pushButton_8_clicked()
{
    satStepOption = 3;
    QString info;
        if (solut == 5)
        {
            info = QString("请先求解CNF公式！\n");
            ui->plainTextEdit_2->appendPlainText(info);
            qDebug() <<"请先求解CNF公式！\n";
        }
        if (SaveValue(ValueList,solut,duration,importFileNameSAT))
        {
            info = QString("\n成功存入文件！");
            ui->plainTextEdit_2->appendPlainText(info);
        }
            qDebug() <<"成功存入文件！";
}

// SAT reset复位键
void MainWindow::on_pushButton_13_clicked()
{
    ui->lineEdit_3->setText("");
    ui->lineEdit_2->setText("");
    ui->plainTextEdit->setPlainText("");
    ui->plainTextEdit_2->setPlainText("");
}

