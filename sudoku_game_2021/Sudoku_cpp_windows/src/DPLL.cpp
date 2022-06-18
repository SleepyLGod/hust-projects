/**
 *  DPLL.c
 *  ����SAT��������Ϸ������
 * 
 *  Created by ·껶� on 2021/9/5
 *  Copyright ? 2021 ·껶�. All rights reserved.
**/

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
    int op=1;       //��¼ѡ��Ĳ������
    int choose;     //��¼ѡ����㷨���
    int i=0,solut=0;//solut��¼CNF��ʽ�Ƿ��н⣬�н�Ϊ1���޽�Ϊ0
    clock_t start = 0,finish = 0;//��¼DPLL�������õ���ʼ����ֹʱ��
    double duration=0;//��¼SAT���ʱ��
    FILE *open;
    printf("������������cnf�ļ�����");
    scanf("%s",filename);
    open=fopen(filename, "r");
    if (open==NULL) 
    {
        printf("�ļ��򿪴���\n");
        getchar();getchar();
        return ERROR;
    }
    if (CreateParadigm(&open)==ERROR)
    {//����CNF��ʽ���ݴ洢�ṹ
        getchar();getchar();
        return ERROR;
    }
    
    int decision;
    decision=OccurTimeCount();//Ԥ����CNF��ʽ��Ԫ���ִ�����Ϣ��������ȡ����ѱ�Ԫѡ�����
    op=1;
    solut=5;
    while (op) 
    {
        printf("\t\t Choose an option please.\n");
        printf("---------------------------------------------------------\n");
        printf(" 1.��������   2.��֤CNF��ʽ�������   3.���������\n");
        printf(" 0.�˳�\n");
        printf("---------------------------------------------------------\n");
        scanf("%d",&op);
        switch (op) 
        {
            case 1:
                if (ValueList[1].IsInit==1)
                {
                    printf("�ѶԹ�ʽ��⣡");
                    getchar();getchar();
                    break;
                }
                printf("ʹ�ã�1.�Ż�1�㷨       2.�Ż�2�㷨        3.�Ż�ǰ�㷨\n");
                scanf("%d",&choose);
                switch (choose) 
                {
                    case 1:
                        if (decision==1) 
                        {
                            start=clock();
                            solut=DPLL1(FindLiteral1(r),1,1);
                            finish=clock();
                            duration=(double)(finish-start)/1000.0;
                        }
                        else if (decision==2)
                        {
                            start=clock();
                            solut=DPLL2(FindLiteral2(r),1,1);
                            finish=clock();
                            duration=(double)(finish-start)/1000.0;
                        }
                        else if (decision==3)
                        {
                            start=clock();
                            solut=DPLL3(FindLiteral3(r),1,1);
                            finish=clock();
                            duration=(double)(finish-start)/1000.0;
                        }
                        else if (decision==4)
                        {
                            start=clock();
                            solut=DPLL4(FindLiteral4(r),1,1);
                            finish=clock();
                            duration=(double)(finish-start)/1000.0;
                        }
                        break;
                    case 2:
                        start=clock();
                        solut=DPLL2(FindLiteral2(r),1,1);
                        finish=clock();
                        duration=(double)(finish-start)/1000.0;
                        break;
                    case 3:
                        start=clock();
                        solut=DPLL_Before(r, 1);
                        finish=clock();
                        duration=(double)(finish-start)/1000.0;
                        break;
                    default:
                        printf("�������\n");
                        break;
                }
                if (solut)
                {
                    AnswerComplete();
                    for (i=1; i<=r->litsize; i++) 
                    {
                        printf("��Ԫ%4d����ֵΪ%d\n",i,ValueList[i].Value);
                    }
                }
                else  
                printf("�ù�ʽ�޽⣡\n");
                printf("����ʱ��Ϊ��%fms\n",(double)(finish-start)/1000.000*1000.0);
                getchar();getchar();
                break;
            case 2:
                if (solut==5)
                {
                    printf("�������CNF��ʽ��\n");
                    getchar();getchar();
                    break;
                }
                ParadigmTrabverse(r);
                if (AnswerCheck(solut)==OK) 
                {
                    printf("��ʽ������ȷ��\n");
                } else 
                {
                    printf("ERROR��\n");
                }
                getchar();getchar();
                break;
            case 3:
                if (solut==5)
                {
                    printf("�������CNF��ʽ��\n");
                    getchar();getchar();
                    break;
                }
                if (SaveValue(ValueList,solut,duration))
                    printf("�ɹ������ļ���");
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
    DestroyParadigm(r);//����CNF��ʽ���ݴ洢�ṹ
    return OK;
}

/*���õ����ֱ�Ԫѡȡ���Եĵݹ��㷨DPLL����
 ������(int)num���ôν��뺯����ֵ��Ϊ1�ı�Ԫ��ţ�
      (int)op����ͨ���cnf�ļ�Ϊ1��������������Ϊ2��
      (int)timesofDPLL����һ�ν���DPLL����Ϊ1�����Ϊ2��
 ����ֵ��FALSE����ʽ�޽⣻
       TRUE����ʽ�н�*/
status DPLL3(int num,int op,int timesofDPLL)
{
    int l,i;
    Clause *c;
    Paradigm *p=r->first;
    Paraline *pline;
    i=0;
    /*���Ӿ����*/
    if (timesofDPLL==1) 
    {
        l=0;//��һ�ν���DPLL�����������뵥�Ӿ�ѭ��
    }
    else
    {
        if (op==1)
            l=num;
        else l=0;
    }
    while (l!=0) 
    {
        stack[++instacksize]=l;//��¼ѭ����������ֵ��Ϊ1������
        DeleteClause(r, l);//ɾ��������l���Ӿ�
        if (DeleteLiteral(r, l)==FALSE){//ɾ���Ӿ�������l�ķ�����
            //��̽���ʽ�޽⣬�ָ��ݹ���뱾�κ���ǰ���ڽ�����״̬
            for (; stack[instacksize]!=num; instacksize--) 
            {
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit=0;
            }
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
            instacksize--;
            return FALSE;
        }
        //�ڱ�Ԫ���м�¼��Ԫl����ֵ
        if (l>0)
        {
            ValueList[l].Value=1;
            ValueList[l].IsInit=1;
        }
        else
        {
            ValueList[0-l].Value=0;
            ValueList[0-l].IsInit=1;
        }
        if (FindLiteral3(r)==0)
            return TRUE;//��ʽ��û��ʣ���Ϊ����ֵ�ı�Ԫ�����ɹ�
        l=HasUnitClause(r);//Ѱ�ҹ�ʽ�еĵ��Ӿ䲢��������ֵ����l
    }
    if (op==1) 
    {
        l=FindLiteral3(r);
    }
    else {
        //����������ʱ��ѡ��һ���������Ϊ��һ����ֵ��Ϊ��ı�Ԫ���
        do {
            l=rand()%729+1;
            for (pline=ValueList[l].Neg.Tra_cla; pline!=NULL; pline=pline->next) 
            {
                p=pline->claline;
                if (p->number!=0)
                    break;
            }
        } while (ValueList[l].IsInit==1);
        for (c=p->sentence; c!=NULL; c=c->nextl) 
        {
            if (c->flag==0)
            {
                l=c->literal;
                break;
            }
        }
    }
    if (l==0)
        return TRUE;//��ʽ��û��ʣ���Ϊ����ֵ�ı�Ԫ�����ɹ�
    if (DPLL3(l, 1,2)) 
    {
        return TRUE;
    }
    l=0-l;//��lΪ��ֵΪ1ʱ̽�����ʧ�ܣ���l��ֵֻ��Ϊ0�����䷴������ֵΪ1
    if (DPLL3(l,1,2)==FALSE) 
    {
        if (instacksize==0)
            return FALSE;//l���Ǳ���DPLL3������һ������̽��ı�Ԫ��̽��ʧ��
        /*�ָ��ݹ���뱾�κ���ǰ���ڽ�����״̬*/
        for (; stack[instacksize]!=num; instacksize--) 
        {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit=0;
        instacksize--;
        return FALSE;  
    } else
        return TRUE;
}

/*���õڶ��ֱ�Ԫѡȡ���Եĵݹ��㷨DPLL����
 ������(int)num���ôν��뺯����ֵ��Ϊ1�ı�Ԫ��ţ�
      (int)op����ͨ���cnf�ļ�Ϊ1��������������Ϊ2��
      (int)timesofDPLL����һ�ν���DPLL����Ϊ1�����Ϊ2��
 ����ֵ��FALSE����ʽ�޽⣻
       TRUE����ʽ�н�*/
status DPLL2(int num,int op,int timesofDPLL)
{
    int l,i;
    Clause *c;
    Paradigm *p=r->first;
    Paraline *pline;
    i=0;
    /*���Ӿ����*/
    if (timesofDPLL==1) 
    {
        l=0;
    }else
    {
        if (op==1)
            l=num;
        else l=0;
    }
    while (l!=0) 
    {
        stack[++instacksize]=l;
        DeleteClause(r, l);
        if (DeleteLiteral(r, l)==FALSE){
            for (; stack[instacksize]!=num; instacksize--) 
            {
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit=0;
            }
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
            instacksize--;
            return FALSE;
        }
        if (l>0)
        {
            ValueList[l].Value=1;
            ValueList[l].IsInit=1;
        }
        else
        {
            ValueList[0-l].Value=0;
            ValueList[0-l].IsInit=1;
        }
        if (FindLiteral2(r)==0)
            return TRUE;
        l=HasUnitClause(r);
    }
    if (op==1) 
    {
        l=FindLiteral2(r);
    }
    else 
    {
        do 
        {
            l=rand()%729+1;
            for (pline=ValueList[l].Neg.Tra_cla; pline!=NULL; pline=pline->next) 
            {
                p=pline->claline;
                if (p->number!=0)
                    break;
            }
        } while (ValueList[l].IsInit==1);
        for (c=p->sentence; c!=NULL; c=c->nextl) 
        {
            if (c->flag==0)
            {
                l=c->literal;
                break;
            }
        }
    }
    if (l==0)
        return TRUE;
    if (DPLL2(l, 1,2))
    {
        return TRUE;
    }
    l=0-l;
    if (DPLL2(l,1,2)==FALSE) 
    {
        if (instacksize==0)
            return FALSE;
        for (; stack[instacksize]!=num; instacksize--) 
        {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit=0;
        instacksize--;
        return FALSE;
    } 
    else
        return TRUE;
}

/*���õ�һ�ֱ�Ԫѡȡ���Եĵݹ��㷨DPLL����
 ������(int)num���ôν��뺯����ֵ��Ϊ1�ı�Ԫ��ţ�
      (int)op����ͨ���cnf�ļ�Ϊ1��������������Ϊ2��
      (int)timesofDPLL����һ�ν���DPLL����Ϊ1�����Ϊ2��
 ����ֵ��FALSE����ʽ�޽⣻
       TRUE����ʽ�н�*/
status DPLL1(int num,int op,int timesofDPLL)
{
    int l,i;
    Clause *c;
    Paradigm *p=r->first;
    Paraline *pline;
    i=0;
    /*���Ӿ����*/
    if (timesofDPLL==1) {
        l=0;
    }else{
        if (op==1)
            l=num;
        else l=0;
    }
    
    while (l!=0) {
        stack[++instacksize]=l;
        DeleteClause(r, l);
        if (DeleteLiteral(r, l)==FALSE){
            for (; stack[instacksize]!=num; instacksize--) {
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit=0;
            }
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
            instacksize--;
            return FALSE;
        }
        if (l>0){
            ValueList[l].Value=1;
            ValueList[l].IsInit=1;
        }else{
            ValueList[0-l].Value=0;
            ValueList[0-l].IsInit=1;
        }
        if (FindLiteral1(r)==0)
            return TRUE;
        l=HasUnitClause(r);
    }
    if (op==1) {
        l=FindLiteral1(r);
    }
    else {
        do {
            l=rand()%729+1;
            for (pline=ValueList[l].Neg.Tra_cla; pline!=NULL; pline=pline->next) {
                p=pline->claline;
                if (p->number!=0)
                    break;
            }
        } while (ValueList[l].IsInit==1);
        for (c=p->sentence; c!=NULL; c=c->nextl) {
            if (c->flag==0){
                l=c->literal;
                break;
            }
        }
    }
    if (l==0)
        return TRUE;
    if (DPLL1(l, 1,2)) {
        return TRUE;
    }
    
    l=0-l;
    if (DPLL1(l,1,2)==FALSE) {
        if (instacksize==0)
            return FALSE;
        for (; stack[instacksize]!=num; instacksize--) {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit=0;
        instacksize--;
        return FALSE;
    } else
        return TRUE;
}

/*���õ����ֱ�Ԫѡȡ���Եĵݹ��㷨DPLL����
 ������(int)num���ôν��뺯����ֵ��Ϊ1�ı�Ԫ��ţ�
      (int)op����ͨ���cnf�ļ�Ϊ1��������������Ϊ2��
      (int)timesofDPLL����һ�ν���DPLL����Ϊ1�����Ϊ2��
 ����ֵ��FALSE����ʽ�޽⣻
       TRUE����ʽ�н�*/
status DPLL4(int num,int op,int timesofDPLL){
    int l,i;
    Clause *c;
    Paradigm *p=r->first;
    Paraline *pline;
    i=0;
    
    /*���Ӿ����*/
    if (timesofDPLL==1) {
        l=0;
    }else{
        if (op==1)
            l=num;
        else l=0;
    }
    while (l!=0) {
        stack[++instacksize]=l;
        DeleteClause(r, l);
        if (DeleteLiteral(r, l)==FALSE){
            for (; stack[instacksize]!=num; instacksize--) {
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit=0;
            }
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
            instacksize--;
            return FALSE;
        }
        if (l>0){
            ValueList[l].Value=1;
            ValueList[l].IsInit=1;
        }else{
            ValueList[0-l].Value=0;
            ValueList[0-l].IsInit=1;
        }
        if (FindLiteral4(r)==0)
            return TRUE;
        l=HasUnitClause(r);
    }
    if (op==1) {
        l=FindLiteral4(r);
    }
    else {
        do {
            l=rand()%729+1;
            for (pline=ValueList[l].Neg.Tra_cla; pline!=NULL; pline=pline->next) {
                p=pline->claline;
                if (p->number!=0)
                    break;
            }
        } while (ValueList[l].IsInit==1);
        for (c=p->sentence; c!=NULL; c=c->nextl) {
            if (c->flag==0){
                l=c->literal;
                break;
            }
        }
    }
    if (l==0)
        return TRUE;
    if (DPLL4(l, 1,2)) {
        return TRUE;
    }
    l=0-l;
    if (DPLL4(l,1,2)==FALSE) {
        if (instacksize==0)
            return FALSE;
        for (; stack[instacksize]!=num; instacksize--) {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit=0;
        instacksize--;
        return FALSE;
    } else
        return TRUE;
}

/*�Ż�ǰ�汾DPLL����
 ������(int)op����ͨ���cnf�ļ�Ϊ1��������������Ϊ2��
 ����ֵ��FALSE����ʽ�޽⣻
       TRUE����ʽ�н�*/
status DPLL_Before(Root *r,int op){
    int l,i;
    Clause *c;
    Paradigm *p=r->first;
    Paraline *pline;
    int *Memory;
    
    /*����Memoryջ����ÿ��DPLLѭ����������ֵ��Ϊ1������*/
    Memory=(int*)malloc((r->litsize)*sizeof(int));
    for (i=0; i<r->litsize; i++)
        Memory[i]=0;
    i=0;
    /*���Ӿ����*/
    if (op==1) {
        c=HasUnitClause_Before(r);
    }
    else {
        c=NULL;
    }
    while (c!=NULL) {
        l=c->literal;
        Memory[i++]=l;
        DeleteClause(r, l);//ɾ��������l���Ӿ�
        if (DeleteLiteral(r, l)==FALSE){//ɾ���־�������l�ĸ�����
             //��̽���ʽ�޽⣬�ָ��ݹ���뱾�κ���ǰ���ڽ�����״̬
            if (Memory[0]!=0)
                RemoveHeadClaus(r, Memory[0]);//ɾ�����ӵĵ��Ӿ�
            for (i=0; Memory[i]!=0; i++){
                RecoverCNF(r, Memory[i]);
                ValueList[abs(Memory[i])].IsInit=0;
                ValueList[abs(Memory[i])].Value=5;
            }
            return FALSE;
        }
        
        /*�ڱ�Ԫ���м�¼��Ԫl����ֵ*/
        if (l>0){
            ValueList[l].Value=1;
            ValueList[l].IsInit=1;
        }else{
            ValueList[0-l].Value=0;
            ValueList[0-l].IsInit=1;
        }
        if (FindLiteral_Before(r)==NULL)
            return TRUE;//��ʽ��û��ʣ���Ϊ����ֵ�ı�Ԫ�����ɹ�
        c=HasUnitClause_Before(r);//Ѱ�ҹ�ʽ�еĵ��Ӿ䲢��������ֵ����l
    }
    
    Memory[i]=0;
    if (op==1) {
        c=FindLiteral_Before(r);
    }
    else {
        do {
            l=rand()%729+1;
            for (pline=ValueList[l].Neg.Tra_cla; pline!=NULL; pline=pline->next) {
                p=pline->claline;
                if (p->number!=0)
                    break;
            }
        } while (ValueList[l].IsInit==1);
        for (c=p->sentence; c!=NULL; c=c->nextl) {
            if (c->flag==0)
                break;
                    }
    }
    if (c==NULL)
        return TRUE;
    l=c->literal;
    AddClause(r, l);//������l��ֵΪ1����CNF��ʽ�ڽ������ͷ���Ӻ�����l�ĵ��Ӿ�����
    if (DPLL_Before(r, 1)) {
        return TRUE;
    }

    l=0-l;//��lΪ��ֵΪ1ʱ̽�����ʧ�ܣ���l��ֵֻ��Ϊ0�����䷴������ֵΪ1
    AddClause(r, l);
    if (DPLL_Before(r,1)==FALSE) {
        
        if (Memory[0]!=0)
            RemoveHeadClaus(r, Memory[0]);
        for (i=0; Memory[i]!=0; i++){
            RecoverCNF(r, Memory[i]);
            ValueList[abs(Memory[i])].IsInit=0;
            ValueList[abs(Memory[i])].Value=5;
        }
        return FALSE;
    } else
        return TRUE;
}

/*��δ����ֵ�ı�Ԫ���������л�����ȥ������ֵ1*/
void AnswerComplete(void){
    int i;
    for (i=1; i<=r->litsize; i++) {
        if (ValueList[i].IsInit==0) {
            ValueList[i].IsInit=1;
            ValueList[i].Value=1;
        }
    }
}

/*���SAT�������ȷ��
 ������(int)solut����ʽ��������н�Ϊ1���޽�Ϊ0��
 ����ֵ��TRUE�������ȷ��
        FALSE��������*/
status AnswerCheck(int solut){
    Paradigm *p;
    Clause *c;
    int flag,l,value,i=0;
    if (solut==1) {//��ʽ�н�
        for (p=r->first; p!=NULL; p=p->nextc) {
            i++;
            flag=0;
            for (c=p->sentence; c!=NULL; c=c->nextl) {
                l=abs(c->literal);
                if (c->literal>0) {
                    value=ValueList[l].Value;
                } else value=1-ValueList[l].Value;
                if (value==1) {
                    flag=1;//�Ӿ�����������ֵΪ1���Ӿ���ֵΪ1
                    break;
                }
            }
            if (flag==0) {
                //
                //printf("��%d��ERROR\n",i);
                //
                return FALSE;//�Ӿ�������ֵΪ1�����֣��Ӿ���ֵΪ0��������
            }
        }
        return TRUE;
    } else {//��ʽ�޽�
        for (p=r->first; p!=NULL; p=p->nextc) {
            flag=0;
            for (c=p->sentence; c!=NULL; c=c->nextl) {
                l=abs(c->literal);
                if (c->literal>0) {
                    value=ValueList[l].Value;
                } else value=1-ValueList[l].Value;
                if (value==1) flag=1;//�Ӿ�����������ֵΪ1���Ӿ���ֵΪ1
            }
            if (flag==0) return TRUE;//�Ӿ���ֵΪ0�������ȷ
        }
        return FALSE;
    }
}

/*���õ���������ѡȡ���Եķǵݹ��㷨DPLL����
 ������(int)num���ôν��뺯����ֵ��Ϊ1�ı�Ԫ��ţ�
       (int)op����ͨ���cnf�ļ�Ϊ1��������������Ϊ2��
       (int)timesofDPLL����һ�ν���DPLL����Ϊ1�����Ϊ2��
 ����ֵ��FALSE����ʽ�޽⣻
        TRUE����ʽ�н�*/
status DPLL(int num,int op,int timesofDPLL){
    int l=num,i;
    int top=0;
    int flag=0;

    Clause *c;
    Paradigm *p=r->first;
    Paraline *pline;
    i=0;
    /*����ջstackmain�洢ͨ������ѡȡ���Ի�õ���ֵ��Ϊ1������*/
    mainstack *stackmain=(mainstack*)malloc(4000*sizeof(mainstack));
    stackmain[0].argue=0;
    stackmain[0].flag=0;

    l=0;
    while (1) {
        while (l!=0) {
            stack[++instacksize]=l;//��¼ѭ����������ֵ��Ϊ1������
            DeleteClause(r, l);//ɾ��������l���Ӿ�
            if (DeleteLiteral(r, l)==FALSE){//ɾ���Ӿ�������l�ķ�����
                //��̽���ʽ�޽⣬�ָ��ݹ����whileѭ��ǰ���ڽ�����״̬
                for (; stack[instacksize]!=stackmain[top].argue; instacksize--) {
                    RecoverCNF(r, stack[instacksize]);
                    ValueList[abs(stack[instacksize])].IsInit=0;
                }
                RecoverCNF(r, stack[instacksize]);
                ValueList[abs(stack[instacksize])].IsInit=0;
                instacksize--;
                
                flag=1;//��Ǹ����ֲ���ʧ��
                break;
            }
            //�ڱ�Ԫ���м�¼��Ԫl����ֵ
            if (l>0){
                ValueList[l].Value=1;
                ValueList[l].IsInit=1;
            }else{
                ValueList[0-l].Value=0;
                ValueList[0-l].IsInit=1;
            }
            if (FindLiteral4(r)==0)
                return TRUE;
            l=HasUnitClause(r);//Ѱ�ҹ�ʽ�еĵ��Ӿ�
        }
        if (op==1) {
            l=FindLiteral4(r);
        }
        else {
            do {
                l=rand()%729+1;
                for (pline=ValueList[l].Neg.Tra_cla; pline!=NULL; pline=pline->next) {
                    p=pline->claline;
                    if (p->number!=0)
                        break;
                }
            } while (ValueList[l].IsInit==1);
            for (c=p->sentence; c!=NULL; c=c->nextl) {
                if (c->flag==0){
                    l=c->literal;
                    break;
                }
            }
        }
        if (l==0)
            return TRUE;//��ʽ��û��ʣ���Ϊ����ֵ�ı�Ԫ�����ɹ�
        if (flag==0) {
            //��һ���ֲ��Գɹ���ֱ��ѡȡ��һ����
            stackmain[++top].argue=l;
            stackmain[top].flag=0;
            continue;//������һ��ѭ��
        }
        if (stackmain[top].flag==0) {//��lΪ��ֵΪ1ʱ̽�����ʧ�ܣ���l��ֵֻ��Ϊ0�����䷴������ֵΪ1
            l=0-stackmain[top].argue;
            stackmain[top].argue=l;
            stackmain[top].flag=1;
        }else{
            /*l���������ֶ��Ѿ����Թ������ʧ�ܣ�����ջ����һ��δ�����䷴���ֵ����ֶ�Ӧ�ڽ�����״̬*/
            while (stackmain[top].flag==1)
                top--;
            l=0-stackmain[top].argue;
            stackmain[top].argue=l;
            stackmain[top].flag=1;
        for (; stack[instacksize]!=0-stackmain[top].argue; instacksize--) {
            RecoverCNF(r, stack[instacksize]);
            ValueList[abs(stack[instacksize])].IsInit=0;
        }
        RecoverCNF(r, stack[instacksize]);
        ValueList[abs(stack[instacksize])].IsInit=0;
        instacksize--;
        }
        
        flag=0;
        if (top==0) {
            return FALSE;
        }
    }

}

