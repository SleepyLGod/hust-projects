/**
 *  Sudoku.c
 *  ����SAT��������Ϸ������
 * 
 *  Created by ·껶� on 2021/9/12
 *  Copyright ? 2021 ·껶�. All rights reserved.
 */

#include "Sudoku.h"


int sudoku_table[9][9];     // ����ȫ�ֱ���int���Ͷ�ά����洢������
int users_sudoku[9][9];     // �洢����ĺ��ո�����������
extern ArgueValue *ValueList;
extern Root *r;

status Sudoku(void)
{
    int op=1,difficulty=0,i,j,flag=1,choose=1;  // op��choose��¼�û�ѡ��Ĳ�����difficulty��¼�û�ѡ������������Ѷ�
    int solut=0;
    char c;
    int x[3];
    srand((unsigned)time(NULL));
    while (op) 
    {
        printf("\t\tChoose an option please.\n");
        printf("---------------------------------------------------------\n");
        printf("  1.������Ϸ         2.���һ�������ļ�         0.�˳�\n");
        printf("---------------------------------------------------------\n");
        scanf("%d",&op);
        switch (op) 
        {
            case 1:
                solut=CreateSudoku();           // ���ɻ����������̶�Ӧ��Ԫ��ֵ��
                if (solut)
                {
                    SudokuComplete();
                    CNFSudokuTableTransform();  // �����ı�Ԫ��ֵ��ת��Ϊ��ά������������
                    SudokuExchange();           // ���ɽ���Ԫ����������Ժ����������
                    printf("��ѡ�������Ѷȣ�\n1.easy\t\t2.medium\t\t3.Hard\n");
                    scanf("%d",&difficulty);
                    // SudokuTablePrint();       // �����þ䣬��������̴�
                    printf("Loading...");

                    /* �����û�ѡ�����������Ѷȶ����������������Ӧ�����Ķ��������� */
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
                            printf("�������\n");
                            break;
                    }
                    choose=1;
                    while (choose) 
                    {
                        flag=1;   // flag����û�������ȷ�����ȷΪ1������Ϊ0
                        printf("��������ֵ����˳������������Ĵ𰸣�������436����������е����еĿո�������6����ÿ����һ�����ûس����Ͽ���������ɺ�������ո񲢰��س�������\n");
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
                            users_sudoku[x[0]][x[1]]=x[2];  // ��¼�û������
                            c=getchar();
                        }
                        for (i=0; i<9; ++i) 
                        {
                            for (j=0; j<9; ++j)
                                // �Ա��û����������𰸣��ж��������ȷ��
                                if (sudoku_table[i][j]!=users_sudoku[i][j]) 
                                {
                                    printf("�𰸴���\n");
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
                            printf("��ϲ������ȷ��\n");
                            SudokuTablePrint();// �����������
                            choose=0;
                        } else 
                        {
                            printf("�Ƿ�鿴�𰸣� 0.��  1.��\n");
                            scanf("%d",&choose);
                            switch (choose) 
                            {
                                case 1:
                                    break;
                                case 0:
                                    SudokuTablePrint();
                                    break;
                                default:printf("�������\n");
                                    break;
                            }
                        }
                    }
                }
                else  printf("����ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 2:
                SolveSudoku();
                getchar();getchar();
                break;
            case 0:
                break;
            default:
                printf("�������");
                getchar();getchar();
                break;
        }
    }
    return OK;
}


/* ������������ת��ΪSAT������cnf�ļ� */
FILE * CreateSudokuFile(void)
{
    int x,y,z,i,j,k,l;                  // x�����������У�y�����������У�zȡ1��9�ֱ����ø�����������ֵΪ1��9����һֵ
    FILE *fp;
    fp=fopen("SudokuTableBase.cnf", "wb");
    if (fp==NULL) 
    {
        printf("�ļ���ʧ�ܣ�\n");
        return NULL;
    }
    fprintf(fp, "p cnf 729 10287\n");   // ����729����Ԫ��9*9�������ո�ÿ�����Ӧ9����Ԫ������1��9��ĳһֵ���Ӧ��ԪΪ�棬����Ϊ��
    for (x=0; x<9; ++x) 
    {
        for (y=0; y<9; ++y)
            for (z=1; z<9; ++z)
                for (i=z+1; i<=9; ++i)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*x+9*y+i));
    }                                   // ÿ��cellֻ��ȡ1��9��һ��ֵ
    for (x=0; x<9; ++x) 
    {
        for (z=1; z<=9; ++z)
            for (y=0; y<8; ++y)
                for (i=y+1; i<=8; ++i)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*x+9*i+z));
    }                                   // ÿ��1��9ֻ�ܸ�����һ��
    for (y=0; y<9; ++y) 
    {
        for (z=1; z<=9; ++z)
            for (x=0; x<8; ++x)
                for (i=x+1; i<=8; ++i)
                    fprintf(fp, "%d %d 0\n",-(81*x+9*y+z),-(81*i+9*y+z));
    }                                    // ÿ��1��9ֻ�ܸ�����һ��
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
    }                                   // ÿ��region��1��9ֻ�ܸ�����һ��
    for (x=0; x<9; ++x) 
    {
        for (y=0; y<9; ++y)
        {
            for (z=1; z<=9; ++z)
                fprintf(fp, "%d ",81*x+9*y+z);
            fprintf(fp, "0\n");
        }
    }                                   // ÿ��cell����ȡ1��9�е�һ��ֵ
    fclose(fp);
    fp=fopen("SudokuTableBase.cnf", "r");
    return fp;
}


/* �����µ����9*9�������� */
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
            printf("�ļ���ʧ�ܣ�\n");
            return ERROR;
        }
        CreateParadigm(&fp);            // ���������ļ���ӦCNF��ʽ�ڽ�����

        /* ��1��81�����ֽ���������� */
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
        {                               // �����������ѡ10�������������1~9
            x=(order[i]-1)/9;           // ˳��Ϊi��cell�����̵�����
            y=(order[i]-1)%9;           // ��cell�����̵�����
            z=rand()%9+1;               // 1��9�������

            /* ���Ѿ�ȷ����cell��ֵ�����Ԫ��ֵ���� */
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
    } while (DPLL2(FindLiteral2(r),2,1)==FALSE);    // ����SAT�������⣬ֱ���õ���������
    return OK;
}

/* �������cnf�ļ���ת��Ϊ����������ʽ��� */
status SolveSudoku(void)
{
    FILE *fp;
    char filename[100];
    char read;
    int i,j,k,x,y,d,cham;
    int exitnum[10];
    printf("������洢�������ļ�����");
    scanf("%s",filename);
    fp=fopen(filename, "r");
    if (fp==NULL) 
    {
        printf("�ļ��򿪴���\n");
        return ERROR;
    }
    for (i=0; i<2; ++i) 
    {
        fscanf(fp, "%c",&read);
        while (read!='\n')
            fscanf(fp, "%c",&read);
    }
    
    /* ��ȡ�����ļ��е����������� */
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
    CreateParadigm(&fp);    // ���������ļ���ӦCNF��ʽ�ڽ�������Ԫ��
    
    /* ���������ļ��еõ�����֪������Ϣ��������Ԫ��cell����ֵ�Ķ�Ӧ��ϵ */
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
                }   // �����У���¼�����Ѵ��ڵ���
                for (x=0; x<9; ++x) 
                {
                    exitnum[sudoku_table[x][j]]=1;
                }   // �����У���¼�����Ѵ��ڵ���
                for (x=(i/3)*3; x<(i/3)*3+3; ++x) 
                {
                    for (y=(j/3)*3; y<(j/3)*3+3; ++y)
                        exitnum[sudoku_table[x][y]]=1;
                }   // ����region����¼region���Ѵ��ڵ���
                for (cham=1; cham<=9; ++cham)
                    if (exitnum[cham]==0) 
                    {
                        ValueList[k].xyz.x=i;       // ��¼�ñ�Ԫ��Ӧ������cell������
                        ValueList[k].xyz.y=j;       // ��¼�ñ�Ԫ��Ӧ������cell������
                        ValueList[k].xyz.z=cham;    // ��¼�ñ�Ԫ��Ӧ������������ֵ
                        ++k;                        // ������һ��Ԫ
                    }
            }
    }
    
    DPLL1(FindLiteral1(r), 1,1);    // ��������ļ�
    for (k=1; k<=r->litsize; ++k) 
    {
        if (ValueList[k].Value==1)
            sudoku_table[ValueList[k].xyz.x][ValueList[k].xyz.y]=ValueList[k].xyz.z;
    }   // ����Ԫ����ֵ��Ϣת��Ϊ��ά�����������Ϣ
    printf("�����Ľ�Ϊ��\n");
    SudokuTablePrint();             // �����������
    return OK;
    }

/* 
 *����֪����������num����������Ψһ�����������
 *������(int)num���ڶ�����Ŀ
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
        printf("�ļ���ʧ�ܣ�\n");
        return ERROR;
    }
    CreateParadigm(&fp);
    
    /* ��������Ϣ�����Ӧ��Ԫ��ֵ���У�����CNF��ʽ�ڽ���������Ӧ���� */
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
    
    /* ����sudoku_table��ֵ������table_diged */
    for (i=0; i<9; ++i)
        for (j=0; j<9; ++j)
            table_diged[i][j]=sudoku_table[i][j];
    
    /* �ڵ�һ���� */
    rank=rand()%81+1;
    diged_cells[rank]=1;
    x=(rank-1)/9;           // ˳��Ϊrank��cell�����̵�����
    y=(rank-1)%9;           // ��cell�����̵�����
    origin=sudoku_table[x][y];
    table_diged[x][y]=0;    // ��¼�ڶ���λ��
    
    /* ��CNF��ʽ�ڽ�����ָ���δ֪��һ����λ�õ�����ֵ�������Ӧ��Ԫ��ֵʱ��״̬ */
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
        /* ÿ��ѭ�����½�����ǰ������Ϣ��ӦCNF��ʽ�ڽ�������Ԫ���Ա�Ԫ��������Ӧ��Ϣ */
        fp=CreateSudokuFile();
        if (fp==NULL) 
        {
            printf("�ļ���ʧ�ܣ�\n");
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
        
        /* ����һ���� */
        rank=rand()%81+1;
        x=(rank-1)/9;        // ˳��Ϊrank��cell�����̵�����
        y=(rank-1)%9;        // ��cell�����̵�����
        if (diged_cells[rank]==1) 
        {
            circle--;        // �ö��Ѿ����ڹ�
            continue;
        }
        diged_cells[rank]=1; // ��¼�ڶ���λ��
        origin=sudoku_table[x][y];
        table_diged[x][y]=0;
        
        /*  ���ڶ�λ�������ԭ������ֵ���8����ֵ��������SAT�����������⣬���н���˵���ڶ���ⲻΨһ���ö������� */
        for (z=1; z<=9; ++z) 
        {
            result=0;
            if (z!=origin)
            {
                /* ����CNF��ʽ���� */
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
            circle--;   // ����ѭ���ڶ����ɹ�
            continue;
        }
        DestroyParadigm(r);
    }
    
    printf("Complete!\n");

    /* ������ɵ������� */
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
            users_sudoku[i][j]=table_diged[i][j];/* ����table_diged��ֵ������users_sudoku */
    return OK;
}

/* ������������ */
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

/* ����cellԪ�ؽ���ԭ������һ�������̵������ */
status SudokuExchange(void)
{
    int x1,y1,x2,y2,x,y;
    int a,b;
    int flag=0;
    int i;
    for (i=0; i<50; ++i) 
    {
        
        // ���ȡ����������cell��ֵ�������a��b
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
        
        /* ������������������cellȡֵΪa��b��λ�ý��н��� */
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
    }   // ����50�����Ԫ�ؽ���
    return OK;
}

/* ������ӦSAT��Ԫ��ת��Ϊ��ά���� */
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

/* ��������� */
status SudokuTablePrint(void)
{
    int i,j;
    printf("   0   1   2   3   4   5   6   7   8  \n");  // �б��
    printf(" +---+---+---+---+---+---+---+---+---+\n");
    for (i=0; i<9; ++i) 
    {   
        printf("%d",i);                                  // �б��
        for (j=0; j<9; ++j)
        {
            if (j==0||j==3||j==6) 
            {
                printf("|");                             // region������
            }
            else printf(" ");
            printf(" %d ",sudoku_table[i][j]);
        }
        printf("|\n");
        if (i==2||i==5||i==8) 
        {
            printf(" +---+---+---+---+---+---+---+---+---+\n");   // region������
        }
        else printf(" |           |           |           |\n");  // region������
    }
    return OK;
}
