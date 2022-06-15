/**
 *  Sudoku.c
 *  基于SAT的数独游戏求解程序
 * 
 *  Created by 路昊东 on 2021/9/12
 *  Copyright ? 2021 路昊东. All rights reserved.
 */

#include "Sudoku.h"


int sudoku_table[9][9];     // 定义全局变量int类型二维数组存储数独盘
int users_sudoku[9][9];     // 存储输出的含空格数独问题格局
extern ArgueValue *ValueList;
extern Root *r;

status Sudoku(void)
{
    int op=1,difficulty=0,i,j,flag=1,choose=1;  // op和choose记录用户选择的操作，difficulty记录用户选择的数独问题难度
    int solut=0;
    char c;
    int x[3];
    srand((unsigned)time(NULL));
    while (op) 
    {
        printf("\t\tChoose an option please.\n");
        printf("---------------------------------------------------------\n");
        printf("  1.数独游戏         2.求解一个数独文件         0.退出\n");
        printf("---------------------------------------------------------\n");
        scanf("%d",&op);
        switch (op) 
        {
            case 1:
                solut=CreateSudoku();           // 生成基础数独终盘对应变元真值表
                if (solut)
                {
                    SudokuComplete();
                    CNFSudokuTableTransform();  // 将求解的变元真值表转换为二维数组数独终盘
                    SudokuExchange();           // 生成交换元素增加随机性后的数独终盘
                    printf("请选择数独难度：\n1.easy\t\t2.medium\t\t3.Hard\n");
                    scanf("%d",&difficulty);
                    // SudokuTablePrint();       // 测试用句，先输出终盘答案
                    printf("Loading...");

                    /* 根据用户选择数独问题难度对数独终盘随机挖相应数量的洞生成问题 */
                    switch (difficulty) 
                    {
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
                    choose=1;
                    while (choose) 
                    {
                        flag=1;   // flag标记用户求解答案正确与否，正确为1，错误为0
                        printf("按“行列值”的顺序，依次输入你的答案（例：“436”代表第四行第三列的空格内填入6），每输入一个答案用回车键断开，输入完成后请输入空格并按回车继续：\n");
                        getchar();
                        c=getchar();
                        while (c!='\n') 
                        {
                            i=0;
                            while (c!=' ') 
                            {
                                x[++i]=c-'0';
                                c=getchar();
                            }
                            users_sudoku[x[0]][x[1]]=x[2];  // 记录用户输入答案
                            c=getchar();
                        }
                        for (i=0; i<9; ++i) 
                        {
                            for (j=0; j<9; ++j)
                                // 对比用户解答和数独答案，判断其求解正确性
                                if (sudoku_table[i][j]!=users_sudoku[i][j]) 
                                {
                                    printf("答案错误！\n");
                                    flag=0;
                                    break;
                                }
                            if (flag==0) 
                            {
                                break;
                            }
                        }
                        if (flag) 
                        {
                            printf("恭喜！答案正确！\n");
                            SudokuTablePrint();// 输出数独终盘
                            choose=0;
                        } else 
                        {
                            printf("是否查看答案？ 0.是  1.否\n");
                            scanf("%d",&choose);
                            switch (choose) 
                            {
                                case 1:
                                    break;
                                case 0:
                                    SudokuTablePrint();
                                    break;
                                default:printf("输入错误！\n");
                                    break;
                            }
                        }
                    }
                }
                else  printf("生成失败！\n");
                getchar();getchar();
                break;
            case 2:
                SolveSudoku();
                getchar();getchar();
                break;
            case 0:
                break;
            default:
                printf("输入错误！");
                getchar();getchar();
                break;
        }
    }
    return OK;
}


/* 创建数独问题转化为SAT问题后的cnf文件 */
FILE * CreateSudokuFile(void)
{
    int x,y,z,i,j,k,l;                  // x代表数独的行，y代表数独的列，z取1～9分别代表该格中数独填入值为1～9中任一值
    FILE *fp;
    fp=fopen("SudokuTableBase.cnf", "wb");
    if (fp==NULL) 
    {
        printf("文件打开失败！\n");
        return NULL;
    }
    fprintf(fp, "p cnf 729 10287\n");   // 共有729个变元，9*9个数独空格每个格对应9个变元，填入1～9中某一值则对应变元为真，其他为假
    for (x=0; x<9; ++x) 
    {
        for (y=0; y<9; ++y)
            for (z=1; z<9; ++z)
                for (i=z+1; i<=9; ++i)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*x+9*y+i));
    }                                   // 每个cell只能取1～9的一个值
    for (x=0; x<9; ++x) 
    {
        for (z=1; z<=9; ++z)
            for (y=0; y<8; ++y)
                for (i=y+1; i<=8; ++i)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*x+9*i+z));
    }                                   // 每行1～9只能各出现一次
    for (y=0; y<9; ++y) 
    {
        for (z=1; z<=9; ++z)
            for (x=0; x<8; ++x)
                for (i=x+1; i<=8; ++i)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*i+9*y+z));
    }                                    // 每列1～9只能各出现一次
    for (i=0; i<3; ++i) 
    {
        for (j=0; j<3; ++j)
            for (z=1; z<=9; ++z)
                for (x=0; x<3; ++x)
                    for (y=0; y<3; ++y)
                        for (k=x+1; k<3; ++k)
                            for (l=0; l<3; l++)
                                if (y!=l)
                                    fprintf(fp, "%d %d 0\n",-(81*(3*i+x)+9*(3*j+y)+z),-(81*(3*i+k)+9*(3*j+l)+z));
    }                                   // 每个region中1～9只能各出现一次
    for (x=0; x<9; ++x) 
    {
        for (y=0; y<9; ++y)
        {
            for (z=1; z<=9; ++z)
                fprintf(fp, "%d ",81*x+9*y+z);
            fprintf(fp, "0\n");
        }
    }                                   // 每个cell必须取1～9中的一个值
    fclose(fp);
    fp=fopen("SudokuTableBase.cnf", "r");
    return fp;
}


/* 创建新的随机9*9数独终盘 */
status CreateSudoku(void)
{
    int x,y,z,i,d;
    int order[82],randnum;
    FILE *fp;
    for (x=0; x<9; ++x)
        for (y=0; y<9; ++y)
            sudoku_table[x][y]=0;
    do {
        fp=CreateSudokuFile();
        if (fp==NULL) 
        {
            printf("文件打开失败！\n");
            return ERROR;
        }
        CreateParadigm(&fp);            // 创建数独文件对应CNF范式邻接链表

        /* 对1～81的数字进行随机排序 */
        for (i=0; i<=81; ++i)
            order[i]=i;
        for (i=81; i>2; i--) 
        {
            randnum=rand()%i+1;
            if (i!=randnum) 
            {
                d=order[i];
                order[i]=order[randnum];
                order[randnum]=d;
            }
        }
        for (i=1; i<=10; ++i) 
        {                               // 在棋盘中随机选10个格子随机填入1~9
            x=(order[i]-1)/9;           // 顺序为i的cell在棋盘的行数
            y=(order[i]-1)%9;           // 该cell在棋盘的列数
            z=rand()%9+1;               // 1～9的随机数

            /* 将已经确定的cell的值记入变元真值表中 */
            for (d=1; d<=9; ++d) 
            {
                ValueList[81*x+9*y+d].IsInit=1;
                if (d==z)
                {
                    ValueList[81*x+9*y+d].Value=1;
                    DeleteClause(r, (81*x+9*y+d));
                    DeleteLiteral(r, (81*x+9*y+d));
                }
                else 
                {
                    ValueList[81*x+9*y+d].Value=0;
                    DeleteClause(r, -(81*x+9*y+d));
                    DeleteLiteral(r, -(81*x+9*y+d));
                }
            }
            
        }
    } while (DPLL2(FindLiteral2(r),2,1)==FALSE);    // 进入SAT求解器求解，直到得到数独终盘
    return OK;
}

/* 求解数独cnf文件并转化为数独终盘形式输出 */
status SolveSudoku(void)
{
    FILE *fp;
    char filename[100];
    char read;
    int i,j,k,x,y,d,cham;
    int exitnum[10];
    printf("请输入存储数独的文件名：");
    scanf("%s",filename);
    fp=fopen(filename, "r");
    if (fp==NULL) 
    {
        printf("文件打开错误！\n");
        return ERROR;
    }
    for (i=0; i<2; ++i) 
    {
        fscanf(fp, "%c",&read);
        while (read!='\n')
            fscanf(fp, "%c",&read);
    }
    
    /* 读取数独文件中的数独问题盘 */
    for (i=0; i<9; ++i) 
    {
        j=0;
        fscanf(fp, "%c",&read);
        while (read!='\n') 
        {
            if (read=='.') 
            {
                sudoku_table[i][j]=0;
            }
            else if (read<='9'&&read>='1') 
            {
                sudoku_table[i][j]=(int)(read-'0');
            }
            else j=-1;
            ++j;
            fscanf(fp, "%c",&read);
        }
    }
    
    fclose(fp);
    fp=fopen(filename, "r");
    CreateParadigm(&fp);    // 创建数独文件对应CNF公式邻接链表及变元表
    
    /* 处理数独文件中得到的已知数独信息，建立变元与cell填入值的对应关系 */
    k=1;
    for (i=0; i<9; ++i) 
    {
        for (j=0; j<9; ++j)
            if (sudoku_table[i][j]==0) 
            {
                for (d=0; d<=9; ++d)
                    exitnum[d]=0;
                for (y=0; y<9; ++y) 
                {
                    exitnum[sudoku_table[i][y]]=1;
                }   // 处理行，记录行中已存在的数
                for (x=0; x<9; ++x) 
                {
                    exitnum[sudoku_table[x][j]]=1;
                }   // 处理列，记录列中已存在的数
                for (x=(i/3)*3; x<(i/3)*3+3; ++x) 
                {
                    for (y=(j/3)*3; y<(j/3)*3+3; ++y)
                        exitnum[sudoku_table[x][y]]=1;
                }   // 处理region，记录region中已存在的数
                for (cham=1; cham<=9; ++cham)
                    if (exitnum[cham]==0) 
                    {
                        ValueList[k].xyz.x=i;       // 记录该变元对应的数独cell的行数
                        ValueList[k].xyz.y=j;       // 记录该变元对应的数独cell的列数
                        ValueList[k].xyz.z=cham;    // 记录该变元对应的数独的填入值
                        ++k;                        // 处理下一变元
                    }
            }
    }
    
    DPLL1(FindLiteral1(r), 1,1);    // 求解数独文件
    for (k=1; k<=r->litsize; ++k) 
    {
        if (ValueList[k].Value==1)
            sudoku_table[ValueList[k].xyz.x][ValueList[k].xyz.y]=ValueList[k].xyz.z;
    }   // 将变元表真值信息转换为二维数组的数独信息
    printf("数独的解为：\n");
    SudokuTablePrint();             // 输出数独终盘
    return OK;
    }

/* 
 *对已知数独终盘挖num个洞生成有唯一解的数独问题
 *参数：(int)num：挖洞的数目
  */
status DigHole(int num)
{
    int x,y,z,i,j,d;
    int rank,origin,result=0,circle;
    int table_diged[9][9];
    int diged_cells[82];
    FILE *fp;
    
    for (i=0; i<=81; ++i)
        diged_cells[i]=0;
    fp=CreateSudokuFile();
    if (fp==NULL) 
    {
        printf("文件打开失败！\n");
        return ERROR;
    }
    CreateParadigm(&fp);
    
    /* 将数独信息填入对应变元真值表中，并对CNF范式邻接链表作相应处理 */
    for (i=0; i<9; ++i)
        for (j=0; j<9; ++j)
        {
            d=sudoku_table[i][j];
            if (d!=0)
                for (z=1; z<=9; ++z) 
                {
                    ValueList[81*i+9*j+z].IsInit=1;
                    if (d==z)
                        ValueList[81*i+9*j+z].Value=1;
                    else
                        ValueList[81*i+9*j+z].Value=0;
                }
        }
    for (i=1; i<=r->litsize; ++i) 
    {
        if (ValueList[i].Value==1) 
        {
            DeleteClause(r, i);
            DeleteLiteral(r, i);
        }
        else
        {
            DeleteClause(r, 0-i);
            DeleteLiteral(r, 0-i);
        }
    }
    
    /* 复制sudoku_table的值至数组table_diged */
    for (i=0; i<9; ++i)
        for (j=0; j<9; ++j)
            table_diged[i][j]=sudoku_table[i][j];
    
    /* 挖第一个洞 */
    rank=rand()%81+1;
    diged_cells[rank]=1;
    x=(rank-1)/9;           // 顺序为rank的cell在棋盘的行数
    y=(rank-1)%9;           // 该cell在棋盘的列数
    origin=sudoku_table[x][y];
    table_diged[x][y]=0;    // 记录挖洞的位置
    
    /* 将CNF公式邻接链表恢复至未知第一个洞位置的填入值，即其对应变元真值时的状态 */
    for (z=1; z<=9; ++z) 
    {
        if (z==origin)
            RecoverCNF(r, 81*x+9*y+z);
        else RecoverCNF(r, -(81*x+9*y+z));
        ValueList[81*x+9*y+z].IsInit=0;
        ValueList[81*x+9*y+z].Value=0;
    }
    DestroyParadigm(r);
    
    for (circle=1; circle<num; ++circle) 
    {
        /* 每次循环重新建立当前数独信息对应CNF公式邻接链表及变元表并对变元表填入相应信息 */
        fp=CreateSudokuFile();
        if (fp==NULL) 
        {
            printf("文件打开失败！\n");
            return ERROR;
        }
        CreateParadigm(&fp);
        for (i=0; i<9; ++i)
            for (j=0; j<9; ++j) 
            {
                d=table_diged[i][j];
                if (d!=0)
                    for (z=1; z<=9; ++z) 
                    {
                        ValueList[81*i+9*j+z].IsInit=1;
                        if (d==z)
                            ValueList[81*i+9*j+z].Value=1;
                        else
                            ValueList[81*i+9*j+z].Value=0;
                    }
            }
        for (i=1; i<=r->litsize; ++i) 
        {
            if (ValueList[i].Value==1) 
            {
                DeleteClause(r, i);
                DeleteLiteral(r, i);
            }
            else
            {
                DeleteClause(r, 0-i);
                DeleteLiteral(r, 0-i);
            }
        }
        
        /* 挖下一个洞 */
        rank=rand()%81+1;
        x=(rank-1)/9;        // 顺序为rank的cell在棋盘的行数
        y=(rank-1)%9;        // 该cell在棋盘的列数
        if (diged_cells[rank]==1) 
        {
            circle--;        // 该洞已经被挖过
            continue;
        }
        diged_cells[rank]=1; // 记录挖洞的位置
        origin=sudoku_table[x][y];
        table_diged[x][y]=0;
        
        /*  对挖洞位置填入除原终盘数值外的8个数值，依次用SAT求解器进行求解，如有解则说明挖洞后解不唯一，该洞不可挖 */
        for (z=1; z<=9; ++z) 
        {
            result=0;
            if (z!=origin)
            {
                /* 处理CNF范式链表 */
                for (d=1; d<=9; ++d) 
                {
                    ValueList[81*x+9*y+d].IsInit=1;
                    if (d==z) 
                    {
                        ValueList[81*x+9*y+d].Value=1;
                        DeleteClause(r, 81*x+9*y+d);
                        DeleteLiteral(r, 81*x+9*y+d);
                    } else 
                    {
                        ValueList[81*x+9*y+d].Value=0;
                        DeleteClause(r, -(81*x+9*y+d));
                        DeleteLiteral(r, -(81*x+9*y+d));
                    }
                }
                DPLL1(FindLiteral1(r), 1,1);
                SudokuComplete();
                result=AnswerCheck(1);
                if (result==1)
                {
                    table_diged[x][y]=origin;
                    break;
                } else
                { 
                    for (d=1; d<=9; ++d) 
                    {
                        if (d==z)
                            RecoverCNF(r, 81*x+9*y+d);
                        else RecoverCNF(r, -(81*x+9*y+d));
                        ValueList[81*x+9*y+d].IsInit=0;
                        ValueList[81*x+9*y+d].Value=0;
                    }
                }
            }
        }
        if (result==1) 
        {
            circle--;   // 本次循环挖洞不成功
            continue;
        }
        DestroyParadigm(r);
    }
    
    printf("Complete!\n");

    /* 输出生成的数独题 */
    printf("   0   1   2   3   4   5   6   7   8  \n");
    printf(" +---+---+---+---+---+---+---+---+---+\n");
    for (i=0; i<9; ++i) 
    {
        printf("%d",i);
        for (j=0; j<9; ++j)
        {
            if (j==0||j==3||j==6) 
            {
                printf("|");
            }
            else printf(" ");
            if (table_diged[i][j]!=0)
                printf(" %d ",table_diged[i][j]);
            else
                printf("   ");
        }
        printf("|\n");
        if (i==2||i==5||i==8) 
        {
            printf(" +---+---+---+---+---+---+---+---+---+\n");
        }
        else printf(" |           |           |           |\n");
    }
    for (i=0; i<9; ++i)
        for (j=0; j<9; ++j)
            users_sudoku[i][j]=table_diged[i][j];/* 复制table_diged的值至数组users_sudoku */
    return OK;
}

/* 完善数独终盘 */
status SudokuComplete(void)
{
    int i,j,z,y,d;
    int complete_table[9][9];
    for (i=0; i<9; ++i)
        for (j=0; j<9; ++j)
            complete_table[i][j]=0;
    for (i=0; i<9; ++i)
        for (j=0; j<9; ++j)
            for (z=1; z<=9; ++z)
                if (ValueList[81*i+9*j+z].Value==1)
                    complete_table[i][j]=z;
                    
    for (i=0; i<9; ++i) 
    {
        for (j=0; j<9; ++j) 
        {
            if (complete_table[i][j]==0) 
            {
                complete_table[i][j]=1;
                for (d=0; d<9; ++d)
                    for (y=0; y<9; ++y)
                        if (y!=j)
                            if (complete_table[i][j]==complete_table[i][y])
                                complete_table[i][j]++;
            }
        }
    }
    for (i=0; i<9; ++i)
        for (j=0; j<9; ++j) 
        {
            d=complete_table[i][j];
            if (d!=0)
                for (z=1; z<=9; ++z) 
                {
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
status SudokuExchange(void)
{
    int x1,y1,x2,y2,x,y;
    int a,b;
    int flag=0;
    int i;
    for (i=0; i<50; ++i) 
    {
        
        // 随机取数独盘两个cell的值记入变量a和b
        x1=rand()%9;
        x2=rand()%9;
        y1=rand()%9;
        y2=rand()%9;
        if (sudoku_table[x1][y1]==sudoku_table[x2][y2]) 
        {
            i--;continue;
        }
        a=sudoku_table[x1][y1];
        b=sudoku_table[x2][y2];
        
        /* 将数独盘上所有列中cell取值为a和b的位置进行交换 */
        for (x=0; x<9; ++x) 
        {
            for (y=0; y<9; ++y) 
            {
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
status CNFSudokuTableTransform(void)
{
    int i,j,z;
    for (i=0; i<9; ++i)
    {
        for (j=0; j<9; ++j)
        {
            for (z=1; z<=9; ++z)
            {
                if (ValueList[81*i+9*j+z].Value==1)
                {
                    sudoku_table[i][j]=z;
                }
            }
        }
    }
    return OK;
}

/* 输出数独盘 */
status SudokuTablePrint(void)
{
    int i,j;
    printf("   0   1   2   3   4   5   6   7   8  \n");  // 列标号
    printf(" +---+---+---+---+---+---+---+---+---+\n");
    for (i=0; i<9; ++i) 
    {   
        printf("%d",i);                                  // 行标号
        for (j=0; j<9; ++j)
        {
            if (j==0||j==3||j==6) 
            {
                printf("|");                             // region间间隔线
            }
            else printf(" ");
            printf(" %d ",sudoku_table[i][j]);
        }
        printf("|\n");
        if (i==2||i==5||i==8) 
        {
            printf(" +---+---+---+---+---+---+---+---+---+\n");   // region间间隔线
        }
        else printf(" |           |           |           |\n");  // region间间隔线
    }
    return OK;
}
