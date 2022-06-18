/**
 *  DPLL.c
 *  基于SAT的数独游戏求解程序
 *  
 *  Created by 路昊东 on 2021/9/10
 *  Copyright ? 2021 路昊东. All rights reserved.
 */

#include "../DPLL.h"

extern ArgueValue *ValueList;
extern Root *r;
extern int *Frequency;
int *stack;
int instacksize;
mainstack *stackmain;
char filename[1000];


status SAT(void)
{
    int op = 1;                           // 记录选择的操作序号
    int choose;                           // 记录选择的算法序号
    int i = 0,solut = 0;                  // solut记录CNF公式是否有解，有解为1，无解为0
    clock_t start = 0.00,finish = 0.00;   // 记录DPLL函数调用的起始和终止时间
    double duration = 0.00;               // 记录SAT求解时间
    FILE *open;
    printf("请输入需求解的cnf文件名：");
    scanf("%s",filename);
    open = fopen(filename, "r");
    if (open == NULL) 
    {
        printf("文件打开错误！\n");
        getchar();getchar();
        return ERROR;
    }
    if (CreateParadigm(&open) == ERROR)
    {   
        // 生成CNF公式数据存储结构
        getchar();getchar();
        return ERROR;
    }
    
    int decision;
    decision = OccurTimeCount();    // 预处理CNF公式变元出现次数信息，决定采取的最佳变元选择策略
    op = 1;
    solut = 5;
    int yyds;
    while (op) 
    {
        printf("\t\t Choose an option please.\n");
        printf("---------------------------------------------------------\n");
        printf(" 1.求解该算例   2.验证CNF公式解析结果   3.保存求解结果\n");
        printf(" 0.退出\n");
        printf("---------------------------------------------------------\n");
        scanf("%d",&op);
        switch (op) 
        {
            case 1:
                if (ValueList[1].IsInit == 1)
                {
                    printf("已对公式求解！");
                    getchar();getchar();
                    break;
                }
                printf("使用：1.优化1算法       2.优化2算法        3.优化前算法\n");
                scanf("%d",&choose);
                switch (choose) 
                {
                    case 1:
                        if (decision == 1) 
                        {
                            yyds = FindLiteral1(r);
                            start = clock();
                            solut = DPLL1(yyds,1,1);
                            finish = clock();
                            duration = (double)(finish-start)/1000.0;
                        }
                        else if (decision == 2)
                        {
                            yyds = FindLiteral2(r);
                            start = clock();
                            solut = DPLL2(yyds,1,1);
                            finish = clock();
                            duration = (double)(finish-start)/1000.0;
                        }
                        else if (decision == 3)
                        {
                            yyds = FindLiteral3(r);
                            start = clock();
                            solut = DPLL3(yyds,1,1);
                            finish = clock();
                            duration = (double)(finish-start)/1000.0;
                        }
                        else if (decision == 4)
                        {
                            yyds = FindLiteral4(r);
                            start = clock();
                            solut = DPLL4(yyds,1,1);
                            finish = clock();
                            duration = (double)(finish-start)/1000.0;
                        }
                        break;
                    case 2:
                        yyds = FindLiteral2(r);
                        start = clock();
                        solut = DPLL2(yyds,1,1);
                        finish = clock();
                        duration = (double)(finish-start)/1000.0;
                        break;
                    case 3:
                        start = clock();
                        solut = DPLL_Before(r, 1);
                        finish = clock();
                        duration = (double)(finish-start)/1000.0;
                        break;
                    default:
                        printf("输入错误！\n");
                        break;
                }
                if (solut)
                {
                    AnswerComplete();
                    for (i = 1; i<= r->litsize; i++) 
                    {
                        printf("变元%4d，真值为%d\n",i,ValueList[i].Value);
                    }
                }
                else  
                printf("该公式无解！\n");
                printf("计算时间为：%fms\n",(double)(finish-start)/1000.0);
                getchar();getchar();
                break;
            case 2:
                if (solut == 5)
                {
                    printf("请先求解CNF公式！\n");
                    getchar();getchar();
                    break;
                }
                ParadigmTrabverse(r);
                if (AnswerCheck(solut) == OK) 
                {
                    printf("公式解析正确！\n");
                } else 
                {
                    printf("ERROR！\n");
                }
                getchar();getchar();
                break;
            case 3:
                if (solut == 5)
                {
                    printf("请先求解CNF公式！\n");
                    getchar();getchar();
                    break;
                }
                if (SaveValue(ValueList,solut,duration))
                    printf("成功存入文件！");
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
    DestroyParadigm(r);     // 销毁CNF公式数据存储结构
    return OK;
}

/* 
 * 采用第三种变元选取策略的递归算法DPLL函数
 * 参数：
 * (int)num：该次进入函数真值设为1的变元序号；
 * (int)op：普通求解cnf文件为1，生成数独终盘为2；
 * (int)timesofDPLL：第一次进入DPLL函数为1，其后为2；
 * 返回值:
 * FALSE：公式无解；
 * TRUE：公式有解
 */
status DPLL3(int num,int op,int timesofDPLL)
{
    int l,i;
    Clause *c;
    Paradigm *p = r->first;
    Paraline *pline;
    i = 0;
    /* 单子句策略 */
    if (timesofDPLL == 1) 
    {
        l = 0;    // 第一次进入DPLL函数，不进入单子句循环
    }
    else
    {
        if (op == 1)
            l = num;
        else l = 0;
    }
    while (l != 0) 
    {
        stack[++instacksize] = l; // 记录循环过程中真值设为1的文字
        DeleteClause(r, l);     // 删除含文字l的子句
        if (DeleteLiteral(r, l) == FALSE)
        {
            // 删除子句中文字l的反文字
            // 如探测后公式无解，恢复递归进入本次函数前的邻接链表状态
            for (; stack[instacksize] != num; instacksize--) 
            {
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit = 0;
            }
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
            instacksize--;
            return FALSE;
        }
        // 在变元表中记录变元l的真值
        if (l>0)
        {
            ValueList[l].Value = 1;
            ValueList[l].IsInit = 1;
        }
        else
        {
            ValueList[0-l].Value = 0;
            ValueList[0-l].IsInit = 1;
        }
        if (FindLiteral3(r) == 0)
            return TRUE;        // 公式中没有剩余的为赋真值的变元，求解成功
        l = HasUnitClause(r);   // 寻找公式中的单子句并将其文字值赋给l
    }
    if (op == 1) 
    {
        l = FindLiteral3(r);
    }
    else 
    {
        // 求数独终盘时，选择一个随机数作为第一个真值设为真的变元序号
        do {
            l = rand()%729+1;
            for (pline = ValueList[l].Neg.Tra_cla; pline != NULL; pline = pline->next) 
            {
                p = pline->claline;
                if (p->number != 0)
                    break;
            }
        } while (ValueList[l].IsInit == 1);
        for (c = p->sentence; c != NULL; c = c->nextl) 
        {
            if (c->flag == 0)
            {
                l = c->literal;
                break;
            }
        }
    }
    if (l == 0)
        return TRUE;        // 公式中没有剩余的为赋真值的变元，求解成功
    if (DPLL3(l, 1,2)) 
    {
        return TRUE;
    }
    l = 0-l;                // 设l为真值为1时探测求解失败，故l真值只能为0，即其反文字真值为1
    if (DPLL3(l,1,2) == FALSE) 
    {
        if (instacksize == 0)
            return FALSE;   // l已是本次DPLL3函数第一个进行探测的变元，探测失败

        /* 恢复递归进入本次函数前的邻接链表状态 */
        for (; stack[instacksize] != num; instacksize--) 
        {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit = 0;
        instacksize--;
        return FALSE;  
    } else
        return TRUE;
}

/* 
 * 采用第二种变元选取策略的递归算法DPLL函数
 * 参数：
 * (int)num：该次进入函数真值设为1的变元序号；
 * (int)op：普通求解cnf文件为1，生成数独终盘为2；
 * (int)timesofDPLL：第一次进入DPLL函数为1，其后为2；
 * 返回值:
 * FALSE：公式无解；
 * TRUE：公式有解
 */
status DPLL2(int num,int op,int timesofDPLL)
{
    int l,i;
    Clause *c;
    Paradigm *p = r->first;
    Paraline *pline;
    i = 0;
    /* 单子句策略 */
    if (timesofDPLL == 1) 
    {
        l = 0;
    }else
    {
        if (op == 1)
            l = num;
        else l = 0;
    }
    while (l != 0) 
    {
        stack[++instacksize] = l;
        DeleteClause(r, l);
        if (DeleteLiteral(r, l) == FALSE){
            for (; stack[instacksize] != num; instacksize--) 
            {
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit = 0;
            }
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
            instacksize--;
            return FALSE;
        }
        if (l>0)
        {
            ValueList[l].Value = 1;
            ValueList[l].IsInit = 1;
        }
        else
        {
            ValueList[0-l].Value = 0;
            ValueList[0-l].IsInit = 1;
        }
        if (FindLiteral2(r) == 0)
            return TRUE;
        l = HasUnitClause(r);
    }
    if (op == 1) 
    {
        l = FindLiteral2(r);
    }
    else 
    {
        do 
        {
            l = rand()%729+1;
            for (pline = ValueList[l].Neg.Tra_cla; pline != NULL; pline = pline->next) 
            {
                p = pline->claline;
                if (p->number != 0)
                    break;
            }
        } while (ValueList[l].IsInit == 1);
        for (c = p->sentence; c != NULL; c = c->nextl) 
        {
            if (c->flag == 0)
            {
                l = c->literal;
                break;
            }
        }
    }
    if (l == 0)
        return TRUE;
    if (DPLL2(l, 1,2))
    {
        return TRUE;
    }
    l = 0-l;
    if (DPLL2(l,1,2) == FALSE) 
    {
        if (instacksize == 0)
            return FALSE;
        for (; stack[instacksize] != num; instacksize--) 
        {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit = 0;
        instacksize--;
        return FALSE;
    } 
    else
        return TRUE;
}

/* 
 * 采用第一种变元选取策略的递归算法DPLL函数
 * 参数：
 * (int)num：该次进入函数真值设为1的变元序号；
 * (int)op：普通求解cnf文件为1，生成数独终盘为2；
 * (int)timesofDPLL：第一次进入DPLL函数为1，其后为2；
 * 返回值:
 * FALSE：公式无解；
 * TRUE：公式有解
 */
status DPLL1(int num,int op,int timesofDPLL)
{
    int l,i;
    Clause *c;
    Paradigm *p = r->first;
    Paraline *pline;
    i = 0;
    /* 单子句策略 */
    if (timesofDPLL == 1) 
    {
        l = 0;
    }else
    {
        if (op == 1)
            l = num;
        else l = 0;
    }
    
    while (l != 0) 
    {
        stack[++instacksize] = l;
        DeleteClause(r, l);
        if (DeleteLiteral(r, l) == FALSE)
        {
            for (; stack[instacksize] != num; instacksize--) 
            {
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit = 0;
            }
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
            instacksize--;
            return FALSE;
        }
        if (l>0)
        {
            ValueList[l].Value = 1;
            ValueList[l].IsInit = 1;
        }else
        {
            ValueList[0-l].Value = 0;
            ValueList[0-l].IsInit = 1;
        }
        if (FindLiteral1(r) == 0)
            return TRUE;
        l = HasUnitClause(r);
    }
    if (op == 1) 
    {
        l = FindLiteral1(r);
    }
    else 
    {
        do {
            l = rand()%729+1;
            for (pline = ValueList[l].Neg.Tra_cla; pline != NULL; pline = pline->next) 
            {
                p = pline->claline;
                if (p->number != 0)
                    break;
            }
        } while (ValueList[l].IsInit == 1);
        for (c = p->sentence; c != NULL; c = c->nextl) 
        {
            if (c->flag == 0)
            {
                l = c->literal;
                break;
            }
        }
    }
    if (l == 0)
        return TRUE;
    if (DPLL1(l, 1,2)) 
    {
        return TRUE;
    }
    
    l = 0-l;
    if (DPLL1(l,1,2) == FALSE) 
    {
        if (instacksize == 0)
            return FALSE;
        for (; stack[instacksize] != num; instacksize--) 
        {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit = 0;
        instacksize--;
        return FALSE;
    } else
        return TRUE;
}

/* 
 * 采用第四种变元选取策略的递归算法DPLL函数
 * 参数：
 * (int)num：该次进入函数真值设为1的变元序号；
 * (int)op：普通求解cnf文件为1，生成数独终盘为2；
 * (int)timesofDPLL：第一次进入DPLL函数为1，其后为2；
 * 返回值:
 * FALSE：公式无解；
 * TRUE：公式有解
 */
status DPLL4(int num,int op,int timesofDPLL)
{
    int l,i;
    Clause *c;
    Paradigm *p = r->first;
    Paraline *pline;
    i = 0;
    
    /* 单子句策略 */
    if (timesofDPLL == 1) 
    {
        l = 0;
    }else
    {
        if (op == 1)
            l = num;
        else l = 0;
    }
    while (l != 0) 
    {
        stack[++instacksize] = l;
        DeleteClause(r, l);
        if (DeleteLiteral(r, l) == FALSE)
        {
            for (; stack[instacksize] != num; instacksize--) 
            {
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit = 0;
            }
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
            instacksize--;
            return FALSE;
        }
        if (l>0)
        {
            ValueList[l].Value = 1;
            ValueList[l].IsInit = 1;
        }else
        {
            ValueList[0-l].Value = 0;
            ValueList[0-l].IsInit = 1;
        }
        if (FindLiteral4(r) == 0)
            return TRUE;
        l = HasUnitClause(r);
    }
    if (op == 1) 
    {
        l = FindLiteral4(r);
    }
    else 
    {
        do 
        {
            l = rand()%729+1;
            for (pline = ValueList[l].Neg.Tra_cla; pline != NULL; pline = pline->next) 
            {
                p = pline->claline;
                if (p->number != 0)
                    break;
            }
        } while (ValueList[l].IsInit == 1);
        for (c = p->sentence; c != NULL; c = c->nextl) 
        {
            if (c->flag == 0)
            {
                l = c->literal;
                break;
            }
        }
    }
    if (l == 0)
        return TRUE;
    if (DPLL4(l, 1,2)) 
    {
        return TRUE;
    }
    l = 0-l;
    if (DPLL4(l,1,2) == FALSE) 
    {
        if (instacksize == 0)
            return FALSE;
        for (; stack[instacksize] != num; instacksize--) 
        {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit = 0;
        instacksize--;
        return FALSE;
    } else
        return TRUE;
}

/* 
 * 优化前版本DPLL函数
 * 参数：(int)op：普通求解cnf文件为1，生成数独终盘为2；
 * 返回值：FALSE：公式无解；
 * TRUE：公式有解
 */
status DPLL_Before(Root *r,int op)
{
    int l,i;
    Clause *c;
    Paradigm *p = r->first;
    Paraline *pline;
    int *Memory;
    
    /* 建立Memory栈保存每次DPLL循环过程中真值设为1的文字 */
    Memory = (int*)malloc((r->litsize)*sizeof(int));
    for (i = 0; i<r->litsize; i++)
        Memory[i] = 0;
    i = 0;
    /* 单子句策略 */
    if (op == 1) 
    {
        c = HasUnitClause_Before(r);
    }
    else 
    {
        c = NULL;
    }
    while (c != NULL) 
    {
        l = c->literal;
        Memory[i++] = l;
        DeleteClause(r, l);     // 删除含文字l的子句
        if (DeleteLiteral(r, l) == FALSE)
        {
            // 删除字句中文字l的负文字
             // 如探测后公式无解，恢复递归进入本次函数前的邻接链表状态
            if (Memory[0] != 0)
                RemoveHeadClaus(r, Memory[0]);  // 删除增加的单子句
            for (i = 0; Memory[i] != 0; i++)
            {
                RecoverCNF(r, Memory[i]);
                ValueList[abs(Memory[i])].IsInit = 0;
                ValueList[abs(Memory[i])].Value = 5;
            }
            return FALSE;
        }
        
        /* 在变元表中记录变元l的真值 */
        if (l>0)
        {
            ValueList[l].Value = 1;
            ValueList[l].IsInit = 1;
        }else
        {
            ValueList[0-l].Value = 0;
            ValueList[0-l].IsInit = 1;
        }
        if (FindLiteral_Before(r) == NULL)
            return TRUE;            // 公式中没有剩余的为赋真值的变元，求解成功
        c = HasUnitClause_Before(r);  // 寻找公式中的单子句并将其文字值赋给l
    }
    
    Memory[i] = 0;
    if (op == 1) 
    {
        c = FindLiteral_Before(r);
    }
    else 
    {
        do 
        {
            l = rand()%729+1;
            for (pline = ValueList[l].Neg.Tra_cla; pline != NULL; pline = pline->next) 
            {
                p = pline->claline;
                if (p->number != 0)
                    break;
            }
        } while (ValueList[l].IsInit == 1);
        for (c = p->sentence; c != NULL; c = c->nextl) 
        {
            if (c->flag == 0)
                break;
        }
    }
    if (c == NULL)
        return TRUE;
    l = c->literal;
    AddClause(r, l);    // 设文字l真值为1，在CNF范式邻接链表表头增加含文字l的单子句链表
    if (DPLL_Before(r, 1)) 
    {
        return TRUE;
    }

    l = 0-l;              // 设l为真值为1时探测求解失败，故l真值只能为0，即其反文字真值为1
    AddClause(r, l);
    if (DPLL_Before(r,1) == FALSE) 
    {
        
        if (Memory[0] != 0)
            RemoveHeadClaus(r, Memory[0]);
        for (i = 0; Memory[i] != 0; i++)
        {
            RecoverCNF(r, Memory[i]);
            ValueList[abs(Memory[i])].IsInit = 0;
            ValueList[abs(Memory[i])].Value = 5;
        }
        return FALSE;
    } else
        return TRUE;
}

/* 将未赋真值的变元（求解过程中化简舍去）赋真值1 */
void AnswerComplete(void)
{
    int i;
    for (i = 1; i<= r->litsize; i++) 
    {
        if (ValueList[i].IsInit == 0) 
        {
            ValueList[i].IsInit = 1;
            ValueList[i].Value = 1;
        }
    }
}

/* 
 * 检查SAT求解结果正确性
 * 参数：(int)solut：公式求解结果，有解为1，无解为0；
 * 返回值：
 * TRUE：求解正确；
 * FALSE：求解错误 
 */
status AnswerCheck(int solut)
{
    Paradigm *p;
    Clause *c;
    int flag,l,value,i = 0;
    if (solut == 1) 
    {
        // 公式有解
        for (p = r->first; p != NULL; p = p->nextc) 
        {
            i++;
            flag = 0;
            for (c = p->sentence; c != NULL; c = c->nextl) 
            {
                l = abs(c->literal);
                if (c->literal>0) 
                {
                    value = ValueList[l].Value;
                } else value = 1-ValueList[l].Value;
                if (value == 1) 
                {
                    flag = 1; // 子句中有文字真值为1，子句真值为1
                    break;
                }
            }
            if (flag == 0) 
            {
                // printf("第%d行ERROR\n",i);
                return FALSE;   // 子句中无真值为1的文字，子句真值为0，求解错误
            }
        }
        return TRUE;
    } else 
    {
        // 公式无解
        for (p = r->first; p != NULL; p = p->nextc) 
        {
            flag = 0;
            for (c = p->sentence; c != NULL; c = c->nextl) 
            {
                l = abs(c->literal);
                if (c->literal>0) 
                {
                    value = ValueList[l].Value;
                } else value = 1-ValueList[l].Value;
                if (value == 1) flag = 1;   // 子句中有文字真值为1，子句真值为1
            }
            if (flag == 0) return TRUE;   // 子句真值为0，求解正确
        }
        return FALSE;
    }
}

/* 
 * 采用第四种文字选取策略的非递归算法DPLL函数
 * 参数：
 * (int)num：该次进入函数真值设为1的变元序号；
 * (int)op：普通求解cnf文件为1，生成数独终盘为2；
 * (int)timesofDPLL：第一次进入DPLL函数为1，其后为2；
 * 返回值：
 * FALSE：公式无解；
 * TRUE：公式有解
 */
status DPLL(int num,int op,int timesofDPLL)
{
    int l = num,i;
    int top = 0;
    int flag = 0;

    Clause *c;
    Paradigm *p = r->first;
    Paraline *pline;
    i = 0;
    /* 建立栈stackmain存储通过文字选取策略获得的真值设为1的文字 */
    mainstack *stackmain = (mainstack*)malloc(4000*sizeof(mainstack));
    stackmain[0].argue = 0;
    stackmain[0].flag = 0;

    l = 0;
    while (1) 
    {
        while (l != 0) 
        {
            stack[++instacksize] = l;     // 记录循环过程中真值设为1的文字
            DeleteClause(r, l);         // 删除含文字l的子句
            if (DeleteLiteral(r, l) == FALSE)
            {
                // 删除子句中文字l的反文字
                // 如探测后公式无解，恢复递归进入while循环前的邻接链表状态
                for (; stack[instacksize] != stackmain[top].argue; instacksize--) 
                {
                    RecoverCNF(r, stack[instacksize]);
                    ValueList[abs(stack[instacksize])].IsInit = 0;
                }
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit = 0;
                instacksize--;
                
                flag = 1; // 标记该文字测试失败
                break;
            }
            // 在变元表中记录变元l的真值
            if (l>0)
            {
                ValueList[l].Value = 1;
                ValueList[l].IsInit = 1;
            }else
            {
                ValueList[0-l].Value = 0;
                ValueList[0-l].IsInit = 1;
            }
            if (FindLiteral4(r) == 0)
                return TRUE;
            l = HasUnitClause(r); // 寻找公式中的单子句
        }
        if (op == 1) 
        {
            l = FindLiteral4(r);
        }
        else 
        {
            do {
                l = rand()%729+1;
                for (pline = ValueList[l].Neg.Tra_cla; pline != NULL; pline = pline->next) 
                {
                    p = pline->claline;
                    if (p->number != 0)
                        break;
                }
            } while (ValueList[l].IsInit == 1);
            for (c = p->sentence; c != NULL; c = c->nextl) 
            {
                if (c->flag == 0)
                {
                    l = c->literal;
                    break;
                }
            }
        }
        if (l == 0)
            return TRUE;    // 公式中没有剩余的为赋真值的变元，求解成功
        if (flag == 0) 
        {
            // 上一文字测试成功，直接选取下一文字
            stackmain[++top].argue = l;
            stackmain[top].flag = 0;
            continue;   // 进入下一次循环
        }
        if (stackmain[top].flag == 0) 
        {
            // 设l为真值为1时探测求解失败，故l真值只能为0，即其反文字真值为1
            l = 0-stackmain[top].argue;
            stackmain[top].argue = l;
            stackmain[top].flag = 1;
        }else
        {
            /* l的正反文字都已经测试过且求解失败，返回栈中上一个未测试其反文字的文字对应邻接链表状态 */
            while (stackmain[top].flag == 1)
                top--;
            l = 0-stackmain[top].argue;
            stackmain[top].argue = l;
            stackmain[top].flag = 1;
        for (; stack[instacksize] != 0-stackmain[top].argue; instacksize--) 
        {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit = 0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit = 0;
        instacksize--;
        }
        
        flag = 0;
        if (top == 0) 
        {
            return FALSE;
        }
    }
}
