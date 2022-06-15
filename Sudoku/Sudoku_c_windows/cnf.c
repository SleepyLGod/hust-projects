/**
 *  cnf.c
 *  ����SAT��������Ϸ������
 *
 *  Created by ·껶� on 2021/9/12 
 *  Copyright ? 2021 ·껶�. All rights reserved.
 */


#include "cnf.h"

ArgueValue *ValueList;
Root *r;
int *Frequency;
extern int *stack;
extern long instacksize;  // ��¼ջstack�Ĵ�С
extern mainstack *stackmain;
extern char filename[1000];

/**
 * ����CNF��ʽ�ڽ�����
 * ������(FILE**)open��
 * �ļ���ָ���ַ
 */
status CreateParadigm(FILE **open)
{
    char readfile[20];   // �����ַ����������¼���ļ��ж���������
    int l,i,j;
    Paradigm *p,*q;
    r=(Root*)malloc(sizeof(Root));
    r->first=NULL;
   
    while (fscanf(*open, "%s",readfile)!=EOF)  // ѭ�����ļ�
    { 
        // �����ļ��ж��������ַ�pʱ����ѭ��
        if (strcmp(readfile,"p")==0)
            break;
    }
    while (fscanf(*open, "%s",readfile)!=EOF) 
    {
        if (strcmp(readfile,"cnf")==0) 
        { 
            // ���ļ��ж����ַ���"cnf"
            fscanf(*open, "%d",&l);
            r->litsize=l;       // ��ȡCNF�ļ���Ԫ������r->litsize
            fscanf(*open, "%d",&l);
            r->parasize=l;      // ��ȡCNF�ļ��Ӿ���������r->parasize
            break;
        }
    }

    /* ������Ԫ�� */
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
        /* ������һ���Ӿ�ͷ��������� */
        if (fscanf(*open, "%d",&l)!=EOF&&l!=0) 
        {
            p=(Paradigm*)malloc(sizeof(Paradigm));
            if (p==NULL) return OVERFLOW;
            r->first=p;q=p;
            p->number=CreateClause(open, &p->sentence, p, l); // �������Ӧ�Ӿ�����
            p->flag=0;
            p->nextc=NULL;
            
            /* ����CNF��ʽ���� */
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
    
     // ����ջstack��¼DPLL��������Ϊ1�����ּ���֮�����ĵ��Ӿ�����
    stack=(int*)malloc(20000*sizeof(int));
    stack[0]=0;
    instacksize=0;
    
    /* ����Ԫ�����ִ����ɶ�������Frequency������˳������ */
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
 * ������
 *    **fp��CNF�ļ�ָ���ַ
 *    **sentence���Ӿ�����ͷ�����Clause����ָ���ַ
 *    *ClausHead���Ӿ�����ͷ���ָ��ֵ
 *    first����CreateParadigm()�����ڶ������Ӿ��һ������ֵ
 *    ����ֵ��
 *    i���Ӿ������ֵ�����
 *    ERROR�����Ӿ�Ϊ���Ӿ�
 *    OVERFLOW���ռ䲻�����
 */
int CreateClause(FILE **fp,Clause **sentence,Paradigm *ClausHead,int first)
{
    Clause *p,*q;
    Paraline *pline;
    int l,l1,i=0;       // i��¼�����Ӿ�����������
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
         // ��������������
        p=(Clause*)malloc(sizeof(Clause));
        if (p==NULL) return OVERFLOW;
        p->literal=l;
        p->flag=0;
        p->nextl=NULL;
        q->nextl=p;
        q=q->nextl;
        i++;
        
         // ������Ԫ����
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
        fscanf(*fp, "%d",&l); // ��ȡ��һ����
    }
    return i;
}

/* ����CNF��ʽ�ڽ����� */
status DestroyParadigm(Root *r)
{
    Paradigm *p;
    Clause *c;
    Paraline *pline;
    int i;
    if (r->first!=NULL) 
    {
        p=r->first;
        /* ����CNF��ʽ���� */
        while (p!=NULL) 
        {
            if (p->sentence!=NULL)
            {
                c=p->sentence;
                /* ���ٵ����Ӿ����� */
                while (c!=NULL) 
                {
                    p->sentence=c->nextl;
                    free(c);    // �ͷŴ洢���ֵĵ����Ӿ�������ռ�
                    c=p->sentence;
                }
            }
            r->first=p->nextc;
            free(p);            // �ͷ��Ӿ�����ͷ���洢�ռ�
            p=r->first;
        }
        
        /* �ͷű�Ԫ����������Ϣ����洢�ռ� */
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
 * �ж�CNF��ʽ���Ƿ���ڵ��Ӿ�
 * �������ͣ�int
 * ����ֵ��
 * ���ڵ��Ӿ䣺�õ��Ӿ�������Ψһ����
 * �����ڵ��Ӿ䣺0 
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
 * �ж�CNF��ʽ���Ƿ���ڵ��Ӿ䣨�Ż�ǰ�汾��
 * �������ͣ�Clause *
 * ����ֵ��
 * ���ڵ��Ӿ䣺�õ��Ӿ���������Ψһ����ָ��
 * �����ڵ��Ӿ䣺NULL 
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
 * �жϲ���ָ��cָ����Ӿ�ͷ����Ӧ�Ӿ��Ƿ�Ϊ���Ӿ䣻
 * ����ֵ��
 * TRUE���ǵ��Ӿ䣻
 * ERROR�����ǵ��Ӿ� 
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

/* ������CNF��ʽ��ȡһ������ */
/* 
 * edition1: ȡÿ��DPLL�����ʽ�г��ִ�����ࣨOccur_Timesֵ��󣩵�����
 * �������ͣ�int
 * ����ֵ��
 * ��ʽ�ǿգ�ѡ�����ֵ�ֵ
 * ��ʽ��û��ʣ�����֣�0 
 */
int FindLiteral1(Root *r)
{
    int i,num=0,flag=0;
    for (i=1; i<=r->litsize; i++) 
    {
        if (ValueList[i].IsInit==0) 
        {
            num=i;  // �ҵ���Ԫ�������һ��δ������ֵ�ı�Ԫ��num��¼�����
            flag=1; // ��ʾ��Ԫ���ڴ���δ������ֵ�ı�Ԫ
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
 * edition2:ȡԭ��ʽ��δ����ֵ�ı�Ԫ�г��ִ�����ࣨOccur_Times��󣩵ı�Ԫ������
 * �������ͣ�int
 * ����ֵ��
 * ��ʽ�ǿգ�ѡ�����ֵ�ֵ
 * ��ʽ��û��ʣ�����֣�0 
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
 * edition3:ȡ�Ӿ��е�һ��δ��ɾ����flagΪ0��������
 * �������ͣ�int
 * ����ֵ��
 * ��ʽ�ǿգ�ѡ�����ֵ�ֵ
 * ��ʽ��û��ʣ�����֣�0 
 */
int FindLiteral3(Root *r)
{
    Paradigm *p;
    Clause *c;
    for (p=r->first; p!=NULL; p=p->nextc)
        if (p->flag==0) 
        { 
            // �Ӿ�δ��ɾ��
            for (c=p->sentence; c!=NULL; c=c->nextl) 
            {
                if (c->flag==0) 
                { 
                    // ����δ��ɾ��
                    return c->literal;
                }
            }
        }
    return 0;
}

/* 
 * edition4: ȡ��Ԫ�����������һ��δ����ֵ��IsInit=0���ı�Ԫ��������
 * �������ͣ�int
 * ����ֵ��
 * ��ʽ�ǿգ�ѡ�����ֵ�ֵ
 * ��ʽ��û��ʣ�����֣�0 
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
 * ������CNF��ʽ��ȡһ�����֣��Ż�ǰ�汾����ȡ�Ӿ��е�һ��δ��ɾ����flagΪ0��������
 * �������ͣ�Clause *
 * ����ֵ��
 * ��ʽ�ǿգ�ѡ�����ֵĽ��ָ��
 * ��ʽ��û��ʣ�����֣�NULL 
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
 * ɾ��������l���Ӿ�
 * ����l����ֵΪ1�����֣�int�� 
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
         // lΪ���������������l��Ӧ��Ԫ����������Ϣ����
        for (pline=ValueList[l1].Pos.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            if (p->flag==0)
            { 
                // pָ����Ӿ�ͷ����Ӧ�Ӿ�δ��ɾ��
                p->flag=l1;                              // ��pָ�����flagֵ���Ϊl����ʾ���Ӿ�������l��ֵΪ1����ɾ��
                r->parasize--;
                for (c=p->sentence; c!=NULL; c=c->nextl) // �����޸�pָ���Ӿ��flag���ֵ
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
         // lΪ���������������l��Ӧ��Ԫ�ĸ�������Ϣ����
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
 * ��CNF��ʽ�ڽ������ͷ���ֻ��������l�ĵ��Ӿ�����
 * ����l��(int)���ӵĵ��Ӿ��ڵ�Ψһ����
 * ����ֵ��
 * OVERFLOW���ռ䲻�������
 * OK���Ӿ����ӳɹ� 
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
        // lΪ�����֣��ڱ�Ԫ����l��Ӧ��Ԫ����������Ϣ�����ͷ�������������Ϣ
        c->litline=ValueList[l1].Pos.Tra_lit;
        ValueList[l1].Pos.Tra_lit=c;
        pline=(Paraline*)malloc(sizeof(Paraline));
        pline->claline=p;
        pline->next=ValueList[l1].Pos.Tra_cla;
        ValueList[l1].Pos.Tra_cla=pline;
    }
    else
    {
        // lΪ�����֣��ڱ�Ԫ����l��Ӧ��Ԫ�ĸ�������Ϣ�����ͷ�������������Ϣ
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
 * ɾ��CNF��ʽ�ڽ������дӱ�ͷ��ʼ��һ��ֻ��������l�ĵ��Ӿ�����
 * ����l��(int)Ҫɾ���ĵ��Ӿ��Ψһ����ֵ��
 * ����ֵ��OK��ɾ���ɹ� 
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
         // lΪ�����֣�Ҫɾ���Ľ����Ϣ���ڱ�Ԫ����l��Ӧ��Ԫ����������Ϣ�����ͷ
        pline=ValueList[l1].Pos.Tra_cla;
        p=pline->claline;
        ValueList[l1].Pos.Tra_cla=pline->next;
        ValueList[l1].Pos.Tra_lit=ValueList[l1].Pos.Tra_lit->litline;
    }
    else
    {
         // lΪ�����֣�Ҫɾ���Ľ����Ϣ���ڱ�Ԫ����l��Ӧ��Ԫ�ĸ�������Ϣ�����ͷ
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
            // Ѱ�Ҵӱ�ͷ��ʼ��һ��ֻ������l�ĵ��Ӿ�
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
 * ɾ����������Ϊ-l���Ӿ�������
 * ����l��(int)��ֵΪ1�����֣�
 * ����ֵ��
 * OK���ɹ�ɾ�����֣�
 * FALSE����ʽ�޽�
 * (�˺�����Ӧʹ��ʽ�е��Ӿ��������٣�
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
                // pָ����Ӿ�����ͷ����Ӧ���Ӿ�δ��ɾ��
                for (c=p->sentence; c!=NULL; c=c->nextl) 
                {
                    if (c->literal==l_op) 
                    {
                        if (c->flag==0) 
                        { 
                            // cָ���Ӿ�������������δ��ɾ��
                            if (p->number==1) return FALSE;             // Ҫɾ��������Ϊ��ǰ�Ӿ��ڵ�Ψһ���֣����Ӿ���ֵΪ0����ʽ�޽�
                            c->flag=l1;                                 // ��Ǹý����flagֵΪl1����ʾ��l��ֵΪ1����ɾ��
                            ValueList[abs(c->literal)].Occur_times--;   // ��Ԫ���ڸñ�Ԫ���ֵĴ�����һ
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
 * �ָ���Ϊ����lΪ��ǰ��CNF�ڽ�����
 * ������(int)����l:��ֵΪ1ʱ������
 * ����ֵ��OK���ڽ�����ָ��ɹ� 
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
        // lΪ�����֣��Ա�Ԫl1����������Ϣ�������������Ѱ�ұ�ɾ�����Ӿ�
        for (pline=ValueList[l1].Pos.Tra_cla; pline!=NULL; pline=pline->next) 
        {
            p=pline->claline;
            if (p->flag==l1) 
            { 
                // pָ����Ӿ�����lΪ���ɾ��
                p->flag=0;
                r->parasize++;
                for (c=p->sentence; c!=NULL; c=c->nextl) 
                {
                    if (c->flag==l1)
                    { 
                        // cָ������ֽ������lΪ�����ɾ��
                        c->flag=0;
                        p->number++;
                    }
                }
            }
        }
         // lΪ�����֣��Ա�Ԫl1�ĸ�������Ϣ�������������Ѱ�ұ�ɾ��������
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
        // lΪ�����֣��Ա�Ԫl1�ĸ�������Ϣ�������������Ѱ�ұ�ɾ�����Ӿ�
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
        // lΪ�����֣��Ա�Ԫl1����������Ϣ�������������Ѱ�ұ�ɾ��������
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

/* ����CNF��ʽ�ڽ���������֤ÿ���Ӿ��Ƿ�Ϊ�� */
void ParadigmTrabverse(Root *r)
{
    Paradigm *p;
    Clause *c;
    int l,value,flag,i=1;
    for (p=r->first; p!=NULL; p=p->nextc) 
    {
        flag=0;
        printf("��%2d�� ",i++);
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
            if (value==1) flag=1;   // �Ӿ��д�����ֵΪ1�����֣��Ӿ���ֵΪ1
            printf("%3d��ֵΪ(%d)  ",c->literal,value);
        }
        printf("%5d\n",flag);
    }
    printf("������ϣ�\n");
}

/* 
 * ����CNF��ʽ�Ľ⼰���ʱ����Ϣ
 * ������
 * (int)solut��CNF��ʽ�Ľ⣬�н�Ϊ1���޽�Ϊ0��
 * (int)time:DPLL���ʱ�䣻
 * ����ֵ:
 * ERROR���ļ���ʧ�ܣ�
 * OK����洢�ɹ� 
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
        printf("�ļ���ʧ�ܣ�\n");
        return ERROR;
    }
    fprintf(save,"s %d", solut);
    fprintf(save, "\nv ");
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
    fprintf(save, "\nt %dms\n",time);
    fclose(save);
    return OK;
}

/* 
 * �����ȡ���ļ��б�Ԫ���ִ�����Ϣ������DPLL�����з��Ѳ��Եı�Ԫѡȡ����
 * ����ֵ��(int)decision��ѡȡ�ı�Ԫѡ����Եı��
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
    
    /* f��¼CNF��ʽ�б�Ԫ���ֵĴ����ͳ��ִ�����ͬ�ı�Ԫ���� */
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
    
    for (i=0; f[i].amount!=0; i++);   // i��¼��Ԫ���ֵĲ�ͬ����������
    
    list.amount=(int*)malloc(i*sizeof(int));
    a=(int*)malloc(i*sizeof(int));
    for (j=0; j<i; j++)
        a[j]=f[j].amount;             // ����f���Ա��нṹ��Աamount��ֵ��int��������a��
    
    /* ������a����ֵ���н������� */
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
    
    /* list�ṹamount�����¼�Բ�ͬ�Ĵ��������ִ�����ͬ�ı�Ԫ������ͬ����Ŀ */
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
    
    /* ��list�ṹ��amount����Ԫ�ؽ��н������� */
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
