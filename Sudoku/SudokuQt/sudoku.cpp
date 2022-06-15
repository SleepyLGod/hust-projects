#include "sudoku.h"
#include "cnf.h"
#include "dpll.h"
extern ArgueValue *ValueList;
extern Root *r;

/* 创建数独问题转化为SAT问题后的cnf文件 */
FILE * CreateSudokuFile(void){
    int x,y,z,i,j,k,l;              // x代表数独的行，y代表数独的列，z取1～9分别代表该格中数独填入值为1～9中任一值
    FILE *fp;
    fp=fopen("SudokuTableBase.cnf", "wb");
    if (fp==NULL) {
        printf("文件打开失败！\n");
        return NULL;
    }
    fprintf(fp, "p cnf 729 10287\n");// 共有729个变元，9*9个数独空格每个格对应9个变元，填入1～9中某一值则对应变元为真，其他为假
    for (x=0; x<9; x++) {
        for (y=0; y<9; y++)
            for (z=1; z<9; z++)
                for (i=z+1; i<=9; i++)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*x+9*y+i));
    }                               // 每个cell只能取1～9的一个值
    for (x=0; x<9; x++) {
        for (z=1; z<=9; z++)
            for (y=0; y<8; y++)
                for (i=y+1; i<=8; i++)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*x+9*i+z));
    }                               // 每行1～9只能各出现一次
    for (y=0; y<9; y++) {
        for (z=1; z<=9; z++)
            for (x=0; x<8; x++)
                for (i=x+1; i<=8; i++)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*i+9*y+z));
    }                               // 每列1～9只能各出现一次
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++)
            for (z=1; z<=9; z++)
                for (x=0; x<3; x++)
                    for (y=0; y<3; y++)
                        for (k=x+1; k<3; k++)
                            for (l=0; l<3; l++)
                                if (y!=l)
                                    fprintf(fp, "%d %d 0\n",-(81*(3*i+x)+9*(3*j+y)+z),-(81*(3*i+k)+9*(3*j+l)+z));
    }                               // 每个region中1～9只能各出现一次
    for (x=0; x<9; x++) {
        for (y=0; y<9; y++){
            for (z=1; z<=9; z++)
                fprintf(fp, "%d ",81*x+9*y+z);
            fprintf(fp, "0\n");
        }
    }                               // 每个cell必须取1～9中的一个值
    fclose(fp);
    fp=fopen("SudokuTableBase.cnf", "r");
    return fp;
}

/* 创建新的随机9*9数独终盘 */
status CreateSudoku(void){
    int x,y,z,i,d;
    int order[82],randnum;
    FILE *fp;
    for (x=0; x<9; x++)
        for (y=0; y<9; y++)
            sudoku_table[x][y]=0;
    do {
        fp=CreateSudokuFile();
        if (fp==NULL) {
            printf("文件打开失败！\n");
            return ERROR;
        }
        CreateParadigm(&fp);    // 创建数独文件对应CNF范式邻接链表

        /* 对1～81的数字进行随机排序 */
        for (i=0; i<=81; i++)
            order[i]=i;
        for (i=81; i>2; i--) {
            randnum=rand()%i+1;
            if (i!=randnum) {
                d=order[i];
                order[i]=order[randnum];
                order[randnum]=d;
            }
        }

        for (i=1; i<=10; i++) { // 在棋盘中随机选10个格子随机填入1~9
            x=(order[i]-1)/9;   // 顺序为i的cell在棋盘的行数
            y=(order[i]-1)%9;   // 该cell在棋盘的列数
            z=rand()%9+1;       // 1～9的随机数

            /* 将已经确定的cell的值记入变元真值表中 */
            for (d=1; d<=9; d++) {
                ValueList[81*x+9*y+d].IsInit=1;
                if (d==z){
                    ValueList[81*x+9*y+d].Value=1;
                    DeleteClause(r, (81*x+9*y+d));
                    DeleteLiteral(r, (81*x+9*y+d));
                }
                else {
                    ValueList[81*x+9*y+d].Value=0;
                    DeleteClause(r, -(81*x+9*y+d));
                    DeleteLiteral(r, -(81*x+9*y+d));
                }
            }

        }
    } while (DPLL2(FindLiteral2(r),2,1)==FALSE);    // 进入SAT求解器求解，直到得到数独终盘
    return OK;
}

/* 对已知数独终盘挖num个洞生成有唯一解的数独问题
 参数：(int)num：挖洞的数目 */
status DigHole(int num){
    int x,y,z,i,j,d;
    int rank,origin,result=0,circle;
    int table_diged[9][9];
    int diged_cells[82];
    FILE *fp;

    for (i=0; i<=81; i++)
        diged_cells[i]=0;
    fp=CreateSudokuFile();
    if (fp==NULL) {
        printf("文件打开失败！\n");
        return ERROR;
    }
    CreateParadigm(&fp);

    /* 将数独信息填入对应变元真值表中，并对CNF范式邻接链表作相应处理 */
    for (i=0; i<9; i++)
        for (j=0; j<9; j++) {
            d=sudoku_table[i][j];
            if (d!=0)
                for (z=1; z<=9; z++) {
                    ValueList[81*i+9*j+z].IsInit=1;
                    if (d==z)
                        ValueList[81*i+9*j+z].Value=1;
                    else
                        ValueList[81*i+9*j+z].Value=0;
                }
        }
    for (i=1; i<=r->litsize; i++) {
        if (ValueList[i].Value==1) {
            DeleteClause(r, i);
            DeleteLiteral(r, i);
        }
        else{
            DeleteClause(r, 0-i);
            DeleteLiteral(r, 0-i);
        }
    }

    /* 复制sudoku_table的值至数组table_diged */
    for (i=0; i<9; i++)
        for (j=0; j<9; j++)
            table_diged[i][j]=sudoku_table[i][j];

    /* 挖第一个洞 */
    rank=rand()%81+1;
    diged_cells[rank]=1;
    x=(rank-1)/9;           // 顺序为rank的cell在棋盘的行数
    y=(rank-1)%9;           // 该cell在棋盘的列数
    origin=sudoku_table[x][y];
    table_diged[x][y]=0;    // 记录挖洞的位置

    /* 将CNF公式邻接链表恢复至未知第一个洞位置的填入值，即其对应变元真值时的状态 */
    for (z=1; z<=9; z++) {
        if (z==origin)
            RecoverCNF(r, 81*x+9*y+z);
        else RecoverCNF(r, -(81*x+9*y+z));
        ValueList[81*x+9*y+z].IsInit=0;
        ValueList[81*x+9*y+z].Value=0;
    }
    DestroyParadigm(r);

    for (circle=1; circle<num; circle++) {
        /* 每次循环重新建立当前数独信息对应CNF公式邻接链表及变元表并对变元表填入相应信息 */
        fp=CreateSudokuFile();
        if (fp==NULL) {
            printf("文件打开失败！\n");
            return ERROR;
        }
        CreateParadigm(&fp);
        for (i=0; i<9; i++)
            for (j=0; j<9; j++) {
                d=table_diged[i][j];
                if (d!=0)
                    for (z=1; z<=9; z++) {
                        ValueList[81*i+9*j+z].IsInit=1;
                        if (d==z)
                            ValueList[81*i+9*j+z].Value=1;
                        else
                            ValueList[81*i+9*j+z].Value=0;
                    }
            }
        for (i=1; i<=r->litsize; i++) {
            if (ValueList[i].Value==1) {
                DeleteClause(r, i);
                DeleteLiteral(r, i);
            }
            else{
                DeleteClause(r, 0-i);
                DeleteLiteral(r, 0-i);
            }
        }

        /* 挖下一个洞 */
        rank=rand()%81+1;
        x=(rank-1)/9;         // 顺序为rank的cell在棋盘的行数
        y=(rank-1)%9;         // 该cell在棋盘的列数
        if (diged_cells[rank]==1) {
            circle--;         // 该洞已经被挖过
            continue;
        }
        diged_cells[rank]=1;  // 记录挖洞的位置
        origin=sudoku_table[x][y];
        table_diged[x][y]=0;

        /* 对挖洞位置填入除原终盘数值外的8个数值，依次用SAT求解器进行求解，如有解则说明挖洞后解不唯一，该洞不可挖 */
        for (z=1; z<=9; z++) {
            result=0;
            if (z!=origin){
                /* 处理CNF范式链表 */
                for (d=1; d<=9; d++) {
                    ValueList[81*x+9*y+d].IsInit=1;
                    if (d==z) {
                        ValueList[81*x+9*y+d].Value=1;
                        DeleteClause(r, 81*x+9*y+d);
                        DeleteLiteral(r, 81*x+9*y+d);
                    } else {
                        ValueList[81*x+9*y+d].Value=0;
                        DeleteClause(r, -(81*x+9*y+d));
                        DeleteLiteral(r, -(81*x+9*y+d));
                    }
                }
                DPLL1(FindLiteral1(r), 1,1);
                SudokuComplete();
                result=AnswerCheck(1);
                if (result==1){
                    table_diged[x][y]=origin;
                    break;
                }
                else{
                    for (d=1; d<=9; d++) {
                        if (d==z)
                            RecoverCNF(r, 81*x+9*y+d);
                        else RecoverCNF(r, -(81*x+9*y+d));
                        ValueList[81*x+9*y+d].IsInit=0;
                        ValueList[81*x+9*y+d].Value=0;
                    }
                }
            }
        }
        if (result==1) {
            circle--;   // 本次循环挖洞不成功
            continue;
        }
        DestroyParadigm(r);
    }
    for (i=0; i<9; i++)
        for (j=0; j<9; j++)
            /* 复制table_diged的值至数组users_sudoku */
            users_sudoku[i][j]=table_diged[i][j];
    return OK;
}

/* 完善数独终盘 */
status SudokuComplete(void){
    int i,j,z,y,d;
    int complete_table[9][9];
    for (i=0; i<9; i++)
        for (j=0; j<9; j++)
            complete_table[i][j]=0;
    for (i=0; i<9; i++)
        for (j=0; j<9; j++)
            for (z=1; z<=9; z++)
                if (ValueList[81*i+9*j+z].Value==1)
                    complete_table[i][j]=z;

    for (i=0; i<9; i++) {
        for (j=0; j<9; j++) {
            if (complete_table[i][j]==0) {
                complete_table[i][j]=1;
                for (d=0; d<9; d++)
                    for (y=0; y<9; y++)
                        if (y!=j)
                            if (complete_table[i][j]==complete_table[i][y])
                                complete_table[i][j]++;
            }
        }
    }
    for (i=0; i<9; i++)
        for (j=0; j<9; j++) {
            d=complete_table[i][j];
            if (d!=0)
                for (z=1; z<=9; z++) {
                    ValueList[81*i+9*j+z].IsInit=1;
                    if (d==z)
                        ValueList[81*i+9*j+z].Value=1;
                    else
                        ValueList[81*i+9*j+z].Value=0;
                }
        }
    return OK;
}

/* 基于cell元素交换原理增加一数独终盘的随机性 */
status SudokuExchange(void){
    int x1,y1,x2,y2,x,y;
    int a,b;
    int flag=0;
    int i;
    for (i=0; i<50; i++) {
        // 随机取数独盘两个cell的值记入变量a和b
        x1=rand()%9;
        x2=rand()%9;
        y1=rand()%9;
        y2=rand()%9;
        if (sudoku_table[x1][y1]==sudoku_table[x2][y2]) {
            i--;continue;
        }
        a=sudoku_table[x1][y1];
        b=sudoku_table[x2][y2];

        /* 将数独盘上所有列中cell取值为a和b的位置进行交换 */
        for (x=0; x<9; x++) {
            for (y=0; y<9; y++) {
                flag=0;
                if (sudoku_table[x][y]==a)
                    flag=1;
                else if (sudoku_table[x][y]==b)
                    flag=2;
                if (flag==1) sudoku_table[x][y]=b;
                else if (flag==2) sudoku_table[x][y]=a;
            }
        }
    }   // 进行50次随机元素交换
    return OK;
}

/* 数独对应SAT变元表转化为二维数组 */
status CNFSudokuTableTransform(void){
    int i,j,z;
    for (i=0; i<9; i++){
        for (j=0; j<9; j++){
            for (z=1; z<=9; z++){
                if (ValueList[81*i+9*j+z].Value==1){
                    sudoku_table[i][j]=z;
                }
            }
        }
    }
    return OK;
}
