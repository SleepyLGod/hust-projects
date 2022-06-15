/**
 *  cnf.c
 *  基于SAT的数独游戏求解程序
 *
 *  Created by 路昊东 on 2021/9/10 
 *  Copyright ? 2021 路昊东. All rights reserved.
 */


#include "../cnf.h"

ArgueValue *ValueList;
Root *r;
int *Frequency;
extern int *stack;
extern long instacksize;  // 记录栈stack的大小
extern mainstack *stackmain;
extern char filename[1000];

/**
 * 创建CNF范式邻接链表
 * 参数：(FILE**)open：
 * 文件的指针地址
 */
status CreateParadigm(FILE **open)
{
    char readfile[20];   // 定义字符类型数组记录在文件中读到的内容
    int l,i,j;
    Paradigm *p,*q;
    r=(Root*)malloc(sizeof(Root));
    r->first=NULL;
   
    while (fscanf(*open, "%s",readfile)!=EOF)  // 循环读文件
    { 
        // 当从文件中读到单个字符p时跳出循环
        if (strcmp(readfile,"p")==0)
            break;
    }
    while (fscanf(*open, "%s",readfile)!=EOF) 
    {
        if (strcmp(readfile,"cnf")==0) 
        { 
            // 从文件中读到字符串"cnf"
            fscanf(*open, "%d",&l);
            r->litsize=l;       // 读取CNF文件变元数存入r->litsize
            fscanf(*open, "%d",&l);
            r->parasize=l;      // 读取CNF文件子句总数存入r->parasize
            break;
        }
    }

    /* 创建变元表 */
    ValueList=(ArgueValue*)malloc((r->litsize+1)*sizeof(ArgueValue));
    if (ValueList==NULL) return OVERFLOW;
    for (i=0; i<=r->litsize; i++)
    {
        ValueList[i].IsInit=0;
        ValueList[i].Occur_times=0;
        ValueList[i].Pos.Tra_cla=NULL;
        ValueList[i].Pos.Tra_lit=NULL;
        ValueList[i].Neg.Tra_cla=NULL;
        ValueList[i].Neg.Tra_lit=NULL;
    }
    Frequency=(int *)malloc((r->litsize)*sizeof(int));
    i=2;
    if (r->parasize!=0) 
    {
        /* 创建第一个子句头结点链表结点 */
        if (fscanf(*open, "%d",&l)!=EOF&&l!=0) 
        {
            p=(Paradigm*)malloc(sizeof(Paradigm));
            if (p==NULL) return OVERFLOW;
            r->first=p;q=p;
            p->number=CreateClause(open, &p->sentence, p, l); // 创建其对应子句链表
            p->flag=0;
            p->nextc=NULL;
            
            /* 创建CNF范式链表 */
            while (i<=r->parasize) 
            {
                i++;
                fscanf(*open, "%d",&l);
                p=(Paradigm*)malloc(sizeof(Paradigm));
                if (p==NULL) return OVERFLOW;
                p->number=CreateClause(open, &p->sentence, p, l);
                p->flag=0;
                p->nextc=NULL;
                q->nextc=p;
                q=q->nextc;
            }
        }
    }
    
     // 创建栈stack记录DPLL过程中设为1的文字及随之产生的单子句文字
    stack=(int*)malloc(20000*sizeof(int));
    stack[0]=0;
    instacksize=0;
    
    /* 将变元按出现次数由多至少在Frequency数组中顺序排列 */
    for (i=0; i<r->litsize; i++)
        Frequency[i]=i+1;
    for (i=0; i<r->litsize; i++) 
    {
        for (j=i+1; j<=r->litsize; j++) 
        {
            if (ValueList[Frequency[i]].Occur_times<ValueList[Frequency[j-1]].Occur_times) 
            {
                l=Frequency[i];
                Frequency[i]=Frequency[j-1];
                Frequency[j-1]=l;
            }
        }
    }

    fclose(*open);
    return OK;
}


/**
 * 
 * 参数：
 *    **fp：CNF文件指针地址
 *    **sentence：子句链表头结点内Clause类型指针地址
 *     *ClausHead：子句链表头结点指针值
 *    first：在CreateParadigm()函数内读到的子句第一个文字值
 * 返回值：
 *    i：子句内文字的数量
 *    ERROR：该子句为空子句
 *    OVERFLOW：空间不足溢出
 */
int CreateClause(FILE **fp,Clause **sentence,Paradigm *ClausHead,int first)
{
    Clause *p,*q;
    Paraline *pline;
    int l,l1,i=0;       // i记录单个子句中文字数量
    if (first==0) return ERROR;
    
    p=(Clause*)malloc(sizeof(Clause));
    if (p==NULL) return OVERFLOW;
    p->literal=first;
    p->flag=0;
    p->nextl=NULL;
    p->litline=NULL;
    q=p;*sentence=p;
    i++;
    
    l1=abs(first);
    ValueList[l1].Occur_times++;
    if (first>0)
    {
        p->litline=ValueList[l1].Pos.Tra_lit;
        ValueList[l1].Pos.Tra_lit=p;
        pline=(Paraline*)malloc(sizeof(Paraline));
        pline->claline=ClausHead;
        pline->next=ValueList[l1].Pos.Tra_cla;
        ValueList[l1].Pos.Tra_cla=pline;
    }
    else 
    {
        p->litline=ValueList[l1].Neg.Tra_lit;
        ValueList[l1].Neg.Tra_lit=p;
        pline=(Paraline*)malloc(sizeof(Paraline));
        pline->claline=ClausHead;
        pline->next=ValueList[l1].Neg.Tra_cla;
        ValueList[l1].Neg.Tra_cla=pline;
    }
    
    fscanf(*fp, "%d",&l);
    while (l!=0) 
    {
         // 创建文字链表结点
        p=(Clause*)malloc(sizeof(Clause));
        if (p==NULL) return OVERFLOW;
        p->literal=l;
        p->flag=0;
        p->nextl=NULL;
        q->nextl=p;
        q=q->nextl;
        i++;
        
         // 创建变元链表
        l1=abs(l);
        ValueList[l1].Occur_times++;
        if (l>0) 
        {
            p->litline=ValueList[l1].Pos.Tra_lit;
            ValueList[l1].Pos.Tra_lit=p;
            pline=(Paraline*)malloc(sizeof(Paraline));
            pline->claline=ClausHead;
            pline->next=ValueList[l1].Pos.Tra_cla;
            ValueList[l1].Pos.Tra_cla=pline;
        }
        else 
        {
            p->litline=ValueList[l1].Neg.Tra_lit;
            ValueList[l1].Neg.Tra_lit=p;
            pline=(Paraline*)malloc(sizeof(Paraline));
            pline->claline=ClausHead;
            pline->next=ValueList[l1].Neg.Tra_cla;
            ValueList[l1].Neg.Tra_cla=pline;
        }
        fscanf(*fp, "%d",&l); // 读取下一文字
    }
    return i;
}

/* 销毁CNF范式邻接链表 */
status DestroyParadigm(Root *r)
{
    Paradigm *p;
    Clause *c;
    Paraline *pline;
    int i;
    if (r->first!=NULL) 
    {
        p=r->first;
        /* 销毁CNF范式链表 */
        while (p!=NULL) 
        {
            if (p->sentence!=NULL)
            {
                c=p->sentence;
                /* 销毁单个子句链表 */
                while (c!=NULL) 
                {
                    p->sentence=c->nextl;
                    free(c);    // 释放存储文字的单个子句链表结点空间
                    c=p->sentence;
                }
            }
            r->first=p->nextc;
            free(p);            // 释放子句链表头结点存储空间
            p=r->first;
        }
        
        /* 释放变元正负文字信息链表存储空间 */
        for (i=0; i<=r->litsize; i++)
        {
            for (pline=ValueList[i].Pos.Tra_cla; pline!=NULL; pline=ValueList[i].Pos.Tra_cla) 
            {
                ValueList[i].Pos.Tra_cla=pline->next;
                free(pline);
            }
            ValueList[i].Pos.Tra_lit=NULL;
            for (pline=ValueList[i].Neg.Tra_cla; pline!=NULL; pline=ValueList[i].Neg.Tra_cla) 
            {
                ValueList[i].Neg.Tra_cla=pline->next;
                free(pline);
            }
            ValueList[i].Neg.Tra_lit=NULL;
        }
    }
    free(Frequency);
    free(r);
    return OK;
}

/* 
 * 判断CNF范式中是否存在单子句
 * 返回类型：int
 * 返回值：
 * 存在单子句：该单子句所含的唯一文字
 * 不存在单子句：0 
 */ 
int HasUnitClause(Root *r)
{
    Paradigm *p;
    Clause *c;
    for (p=r->first; p!=NULL; p=p->nextc) 
    {
        if (p->flag==0)
            if (p->number==1)
            {
                for (c=p->sentence; c!=NULL; c=c->nextl) 
                {
                    if (c->flag==0)
                        return c->literal;
                }
            }
    }
    return 0;
}

/* 
 * 判断CNF范式中是否存在单子句（优化前版本）
 * 返回类型：Clause *
 * 返回值：
 * 存在单子句：该单子句链表所含唯一结点的指针
 * 不存在单子句：NULL 
 */
Clause * HasUnitClause_Before(Root *r)
{
    Paradigm *p;
    Clause *c;
    for (p=r->first; p!=NULL; p=p->nextc) 
    {
        if (p->flag==0)
            if (p->number==1)
            {
                for (c=p->sentence; c!=NULL; c=c->nextl) 
                {
                    if (c->flag==0)
                        return c;
                }
            }
    }
    return NULL;
}

/* 
 * 判断参数指针c指向的子句头结点对应子句是否为单子句；
 * 返回值：
 * TRUE：是单子句；
 * ERROR：不是单子句 
 */
status isUnitClause(Paradigm *c)
{
    if (c->number==1)
        return TRUE;
    else return FALSE;
}
 // int FindLiteral1(Root *r){
 //     int i,num=0,flag=0;
 //     Paradigm *p;
 //     Clause *c;
 //     Paraline *pline;
 //     typedef struct{
 //         int i;
 //         int length;
 //     } Arguelength;
 //     Arguelength *ArgueClaLen;
 //     for (i=1; i<=r->litsize; i++) {
 //         if (ValueList[i].IsInit==0) {
 //             num++;
 //         }
 //     }
 //     ArgueClaLen=(Arguelength*)malloc(num*sizeof(Arguelength));
 //     if (num!=0) {
 //         for (i=1; i<=r->litsize; i++) {
 //             if (ValueList[i].IsInit==0) {
 //                 ArgueClaLen[flag].i=i;
 //                 ArgueClaLen[flag].length=0;
 //                 for (pline=ValueList[i].Pos.Tra_cla; pline!=NULL; pline=pline->next) {
 //                     p=pline->claline;
 //                     if (p->flag!=0) {
 //                         ArgueClaLen[flag].length=ArgueClaLen[flag].length+p->number;
 //                     }
 //                 }
 //                 for (pline=ValueList[i].Neg.Tra_cla; pline!=NULL; pline=pline->next) {
 //                     p=pline->claline;
 //                     if (p->flag!=0) {
 //                         ArgueClaLen[flag].length=ArgueClaLen[flag].length+p->number;
 //                     }
 //                 }
 //                 flag++;
 //             }
 //         }
 //         flag=0;
 //         for (i=1; i<num; i++) {
 //             if (ArgueClaLen[i].length>ArgueClaLen[flag].length) {
 //                 flag=i;
 //             }
 //         }
 //         return ArgueClaLen[flag].i;
 //     }
 // 
 //     return num;
 // }

/* 在整个CNF公式中取一个文字 */
/* 
 * edition1: 取每次DPLL处理后公式中出现次数最多（Occur_Times值最大）的文字
 * 返回类型：int
 * 返回值：
 * 公式非空：选中文字的值
 * 公式中没有剩余文字：0 
 */
int FindLiteral1(Root *r)
{
    int i,num=0,flag=0;
    for (i=1; i<=r->litsize; i++) 
    {
        if (ValueList[i].IsInit==0) 
        {
            num=i;  // 找到变元表正序第一个未被赋真值的变元，num记录其序号
            flag=1; // 表示变元表内存在未被赋真值的变元
            break;
        }
    }
    if (flag==1) 
    {
        for (i++; i<=r->litsize; i++) 
        {
            if (ValueList[i].IsInit==0)
            {
                if (ValueList[i].Occur_times>ValueList[num].Occur_times)
                    num=i;
            }
        }
    }
    return num;
}

/*
 * edition2:取原公式中未赋真值的变元中出现次数最多（Occur_Times最大）的变元正文字
 * 返回类型：int
 * 返回值：
 * 公式非空：选中文字的值
 * 公式中没有剩余文字：0 
 */
int FindLiteral2(Root *r)
{
    int i=0;
    for (i=0; i<r->litsize; i++) 
    {
        if (ValueList[Frequency[i]].IsInit==0) 
        {
            return Frequency[i];
        }
    }
    return 0;
}

/* 
 * edition3:取子句中第一个未被删除（flag为0）的文字
 * 返回类型：int
 * 返回值：
 * 公式非空：选中文字的值
 * 公式中没有剩余文字：0 
 */
int FindLiteral3(Root *r)
{
    Paradigm *p;
    Clause *c;
    for (p=r->first; p!=NULL; p=p->nextc)
        if (p->flag==0) 
        { 
            // 子句未被删除
            for (c=p->sentence; c!=NULL; c=c->nextl) 
            {
                if (c->flag==0) 
                { 
                    // 文字未被删除
                    return c->literal;
                }
            }
        }
    return 0;
}

/* 
 * edition4: 取变元表正序正序第一个未赋真值（IsInit=0）的变元的正文字
 * 返回类型：int
 * 返回值：
 * 公式非空：选中文字的值
 * 公式中没有剩余文字：0 
 */
int FindLiteral4(Root *r)
{
    int i=0;
    for (i=1; i<=r->litsize; i++) 
    {
        if (ValueList[i].IsInit==0) 
        {
            return i;
        }
    }
    return 0;
}

/* 
 * 在整个CNF公式中取一个文字（优化前版本）：取子句中第一个未被删除（flag为0）的文字
 * 返回类型：Clause *
 * 返回值：
 * 公式非空：选中文字的结点指针
 * 公式中没有剩余文字：NULL 
 */
Clause * FindLiteral_Before(Root *r)
{
    Paradigm *p;
    Clause *c;
    for (p=r->first; p!=NULL; p=p->nextc) 
    {
        if (p->flag==0) 
        {
            for (c=p->sentence; c!=NULL; c=c->nextl) 
            {
                if (c->flag==0) 
                {
                    return c;
                }
            }
        }
    }
    return NULL;
}

/* 
 * 删除含参数l的子句
 * 参数l：真值为1的文字（int） 
 */
status DeleteClause(Root *r,int l)
{
    int l1;
    Paradigm *p;
    Clause *c;
    Paraline *pline;
    l1=abs(l);
    if (l>0) 
    {
         // l为正文字情况，搜索l对应变元的正文字信息链表
        for (pline=ValueList[l1].Pos.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            if (p->flag==0)
            { 
                // p指向的子句头结点对应子句未被删除
                p->flag=l1;                              // 将p指向结点的flag值标记为l，表示该子句因文字l真值为1而被删除
                r->parasize--;
                for (c=p->sentence; c!=NULL; c=c->nextl) // 依次修改p指向子句的flag标记值
                    if (c->flag==0)
                    {
                        c->flag=l1;
                        ValueList[abs(c->literal)].Occur_times--;
                        p->number--;
                    }
            }
        }
    }
    else 
    {
         // l为负文字情况，搜索l对应变元的负文字信息链表
        for (pline=ValueList[l1].Neg.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            if (p->flag==0)
            {
                p->flag=l1;
                r->parasize--;
                for (c=p->sentence; c!=NULL; c=c->nextl)
                    if (c->flag==0)
                    {
                        c->flag=l1;
                        ValueList[abs(c->literal)].Occur_times--;
                        p->number--;
                    }
            }
        }
    }
    return OK;
}

/* 
 * 在CNF范式邻接链表表头添加只含有文字l的单子句链表
 * 参数l：(int)增加的单子句内的唯一文字
 * 返回值：
 * OVERFLOW：空间不足溢出；
 * OK：子句增加成功 
 */
status AddClause(Root *r,int l)
{
    Paradigm *p;
    Clause *c;
    Paraline *pline;
    int l1;
    p=(Paradigm*)malloc(sizeof(Paradigm));
    if (p==NULL) return OVERFLOW;
    p->nextc=r->first;
    c=(Clause*)malloc(sizeof(Clause));
    if (c==NULL) return OVERFLOW;
    c->literal=l;
    c->flag=0;
    c->nextl=NULL;
    l1=abs(l);
    if (l>0) 
    {
        // l为正文字，在变元表内l对应变元的正文字信息链表表头增加新增结点信息
        c->litline=ValueList[l1].Pos.Tra_lit;
        ValueList[l1].Pos.Tra_lit=c;
        pline=(Paraline*)malloc(sizeof(Paraline));
        pline->claline=p;
        pline->next=ValueList[l1].Pos.Tra_cla;
        ValueList[l1].Pos.Tra_cla=pline;
    }
    else
    {
        // l为负文字，在变元表内l对应变元的负文字信息链表表头增加新增结点信息
        c->litline=ValueList[l1].Neg.Tra_lit;
        ValueList[l1].Neg.Tra_lit=c;
        pline=(Paraline*)malloc(sizeof(Paraline));
        pline->claline=p;
        pline->next=ValueList[l1].Neg.Tra_cla;
        ValueList[l1].Neg.Tra_cla=pline;
    }
    p->sentence=c;
    p->number=1;
    p->flag=0;
    r->first=p;
    r->parasize++;
    return OK;
}

/* 
 * 删除CNF范式邻接链表中从表头开始第一个只含有文字l的单子句链表
 * 参数l：(int)要删除的单子句的唯一文字值；
 * 返回值：OK：删除成功 
 */
status RemoveHeadClaus(Root *r,int l)
{
    Paradigm *p,*q;
    Clause *c;
    Paraline *pline;
    int l1;
    l1=abs(l);
    if (l>0)
    {
         // l为正文字，要删除的结点信息必在变元表内l对应变元的正文字信息链表表头
        pline=ValueList[l1].Pos.Tra_cla;
        p=pline->claline;
        ValueList[l1].Pos.Tra_cla=pline->next;
        ValueList[l1].Pos.Tra_lit=ValueList[l1].Pos.Tra_lit->litline;
    }
    else
    {
         // l为负文字，要删除的结点信息必在变元表内l对应变元的负文字信息链表表头
        pline=ValueList[l1].Neg.Tra_cla;
        p=pline->claline;
        ValueList[l1].Neg.Tra_cla=pline->next;
        ValueList[l1].Neg.Tra_lit=ValueList[l1].Neg.Tra_lit->litline;
    }
    if (r->first==p) 
    {
        r->first=p->nextc;
    } 
    else 
    {
        for (q=r->first; q!=NULL; q=q->nextc) 
        { 
            // 寻找从表头开始第一个只含文字l的单子句
            if (q->nextc==p)
                break;
        }
        q->nextc=p->nextc;
    }
    c=p->sentence;
    free(c);
    free(p);
    free(pline);
    r->parasize--;
    return  OK;
}

/* 
 * 删除所有文字为-l的子句链表结点
 * 参数l：(int)真值为1的文字；
 * 返回值：
 * OK：成功删除文字；
 * FALSE：公式无解
 * (此函数不应使公式中的子句数量减少）
 */
status DeleteLiteral(Root *r,int l)
{
    Paradigm *p;
    Clause *c;
    Paraline *pline;
    int l1,l_op;
    l1=abs(l);
    l_op=0-l;
    if (l>0)
    {
        for (pline=ValueList[l1].Neg.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            if (p->flag==0) 
            { 
                // p指向的子句链表头结点对应的子句未被删除
                for (c=p->sentence; c!=NULL; c=c->nextl) 
                {
                    if (c->literal==l_op) 
                    {
                        if (c->flag==0) 
                        { 
                            // c指向子句链表结点内文字未被删除
                            if (p->number==1) return FALSE;             // 要删除的文字为当前子句内的唯一文字，该子句真值为0，公式无解
                            c->flag=l1;                                 // 标记该结点内flag值为l1，表示因l真值为1而被删除
                            ValueList[abs(c->literal)].Occur_times--;   // 变元表内该变元出现的次数减一
                            p->number--;
                        }
                    }
                }
            }
        }
    } 
    else 
    {
        for (pline=ValueList[l1].Pos.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            if (p->flag==0) 
            {
                for (c=p->sentence; c!=NULL; c=c->nextl) 
                {
                    if (c->literal==l_op) 
                    {
                        if (c->flag==0) 
                        {
                            if (p->number==1) return FALSE;
                            c->flag=l1;
                            ValueList[abs(c->literal)].Occur_times--;
                            p->number--;
                        }
                    }
                }
            }
        }
    }
    return OK;
}


/* 
 * 恢复认为文字l为真前的CNF邻接链表
 * 参数：(int)文字l:真值为1时求解出错
 * 返回值：OK：邻接链表恢复成功 
 */
status RecoverCNF(Root *r,int l)
{
    Paradigm *p;
    Clause *c;
    Paraline *pline;
    int l1;
    l1=abs(l);
    if (l>0) 
    {
        // l为正文字，对变元l1的正文字信息链表进行搜索，寻找被删除的子句
        for (pline=ValueList[l1].Pos.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            if (p->flag==l1) 
            { 
                // p指向的子句因设l为真而删除
                p->flag=0;
                r->parasize++;
                for (c=p->sentence; c!=NULL; c=c->nextl) 
                {
                    if (c->flag==l1)
                    { 
                        // c指向的文字结点因设l为真而被删除
                        c->flag=0;
                        p->number++;
                    }
                }
            }
        }
         // l为正文字，对变元l1的负文字信息链表进行搜索，寻找被删除的文字
        for (pline=ValueList[l1].Neg.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            for (c=p->sentence; c!=NULL; c=c->nextl) 
            {
                if (c->flag==l1) 
                {
                    c->flag=0;
                    p->number++;
                }
            }
        }
    } 
    else 
    {
        // l为负文字，对变元l1的负文字信息链表进行搜索，寻找被删除的子句
        for (pline=ValueList[l1].Neg.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            if (p->flag==l1) 
            {
                p->flag=0;
                r->parasize++;
                for (c=p->sentence; c!=NULL; c=c->nextl) 
                {
                    if (c->flag==l1)
                    {
                        c->flag=0;
                        p->number++;
                    }
                }
            }
        }
        // l为负文字，对变元l1的正文字信息链表进行搜索，寻找被删除的文字
        for (pline=ValueList[l1].Pos.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            for (c=p->sentence; c!=NULL; c=c->nextl) 
            {
                if (c->flag==l1) 
                {
                    c->flag=0;
                    p->number++;
                }
            }
        }
    }
    return OK;
}

/* 遍历CNF范式邻接链表，并验证每个子句是否为真 */
void ParadigmTrabverse(Root *r)
{
    Paradigm *p;
    Clause *c;
    int l,value,flag,i=1;
    for (p=r->first; p!=NULL; p=p->nextc) 
    {
        flag=0;
        printf("第%2d行 ",i++);
        for (c=p->sentence; c!=NULL; c=c->nextl)
        {
            l=abs(c->literal);
            if (ValueList[l].IsInit==1) 
            {
                if (c->literal>0) 
                {
                    value=ValueList[l].Value;
                } 
                else value=1-ValueList[l].Value;
            } 
            else value=5;
            if (value==1) flag=1;   // 子句中存在真值为1的文字，子句真值为1
            printf("%3d真值为(%d)  ",c->literal,value);
        }
        printf("%5d\n",flag);
    }
    printf("遍历完毕！\n");
}

/* 
 * 保存CNF范式的解及求解时间信息
 * 参数：
 * (int)solut：CNF公式的解，有解为1，无解为0；
 * (int)time:DPLL求解时间；
 * 返回值:
 * ERROR：文件打开失败；
 * OK：解存储成功 
 */
status SaveValue(ArgueValue *ValueList,int solut,int time)
{
    int i=0;
    FILE *save;
    char filenamesave[1000];
    for (i=0; filename[i]!='.'; i++)
        filenamesave[i]=filename[i];
    filenamesave[i++]='.';
    filenamesave[i++]='r';
    filenamesave[i++]='e';
    filenamesave[i++]='s';
    filenamesave[i++]='\0';
    save=fopen(filenamesave, "wb");
    if (save==NULL)
    {
        printf("文件打开失败！\n");
        return ERROR;
    }
    fprintf(save,"%d", solut);
    fprintf(save, "\n");
    for (i=1; i<=r->litsize; i++) 
    {
        if (ValueList[i].IsInit==1) 
        {
            if (ValueList[i].Value==1) 
            {
                fprintf(save, "%d",i);
            }
            else fprintf(save, "%d",0-i);
            fprintf(save, " ");
        }
    }
    fprintf(save, "\n%dms",time);
    fclose(save);
    return OK;
}

/* 
 * 处理读取的文件中变元出现次数信息，决策DPLL过程中分裂策略的变元选取策略
 * 返回值：(int)decision：选取的变元选择策略的编号
 */
int OccurTimeCount(void)
{
    int i,j=0,k,num;
    Frequent *f;
    SameFre_AmountList list;
    int *a;
    int decision=0;
    f=(Frequent*)malloc((r->litsize)*sizeof(Frequent));
    for (i=0; i<r->litsize; i++) 
    {
        f[i].amount=0;
        f[i].number=0;
    }
    
    /* f记录CNF公式中变元出现的次数和出现次数相同的变元数量 */
    f[0].number=ValueList[Frequency[0]].Occur_times;
    f[0].amount++;
    for (i=1; i<r->litsize; i++) 
    {
        if (ValueList[Frequency[i]].Occur_times!=f[j].number) 
        {
            j++;
        }
        f[j].number=ValueList[Frequency[i]].Occur_times;
        f[j].amount++;
    }
    
    for (i=0; f[i].amount!=0; i++);   // i记录变元出现的不同次数的总数
    
    list.amount=(int*)malloc(i*sizeof(int));
    a=(int*)malloc(i*sizeof(int));
    for (j=0; j<i; j++)
        a[j]=f[j].amount;             // 复制f线性表中结构成员amount的值到int类型数组a中
    
    /* 对数组a中数值进行降序排序 */
    for (j=0; j<i-1; j++) 
    {
        for (k=j+1; k<i; k++) 
        {
            if (a[j]<a[k]) 
            {
                num=a[j];
                a[j]=a[k];
                a[k]=num;
            }
        }
    }
    list.totalvariety=0;
    for (j=0; j<i; j++) 
    {
        list.amount[j]=0;
    }
    
    /* list结构amount数组记录对不同的次数，出现次数相同的变元数量相同的数目 */
    list.amount[0]=1;
    list.totalvariety++;
    for (j=1; j<i; j++) 
    {
        if (a[j]!=a[j-1]) 
        {
            list.totalvariety++;
        }
        list.amount[list.totalvariety-1]++;   
    }
    
    /* 对list结构中amount数组元素进行降序排序 */
    for (j=0; j<list.totalvariety-1; j++) 
    {
        for (k=j+1; k<list.totalvariety; k++) 
        {
            if (list.amount[j]<list.amount[k]) 
            {
                num=list.amount[j];
                list.amount[j]=list.amount[k];
                list.amount[k]=num;
            }
        }
    }
    if (list.totalvariety<=2)
        decision=3;
    else if (list.totalvariety>=16)
        decision=4;
    else if (list.totalvariety<10&&list.amount[0]>=4)
        decision=1;
    else
        decision=3;
    
    return decision;
}