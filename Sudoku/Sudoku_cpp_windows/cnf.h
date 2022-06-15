/**
 *  cnf��ʽ
 *  ����SAT��������Ϸ������
 * 
 *  Created by ·껶� on 2021/9/5
 *  Copyright ? 2021 ·껶�. All rights reserved.
**/

#ifndef cnf_h
#define cnf_h

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define INCREASEMENT 100

typedef int status;

/*�����Ӿ�������ṹ����*/
typedef struct Clause
{
    int literal;                //��¼�Ӿ��е�����
    int flag;                   //��Ǹ������Ƿ��ѱ�ɾ����δɾ��ʱֵΪ0������ֵΪʹ֮ɾ���ı�Ԫ���
    struct Clause *nextl;       //ָ����Ӿ�����һ���ֵ�ָ��
    struct Clause *litline;     //ָ������CNF��ʽ�ڽ���������һ��������ͬ���Ӿ���
}Clause;

/*����CNF��ʽ�����㣨���Ӿ�����ͷ��㣩�ṹ����*/
typedef struct Paradigm
{
    int number;                 //�Ӿ�����ʾ��������
    int flag;                   //��Ǹ��Ӿ��Ƿ��ѱ�ɾ����δɾ��ʱֵΪ0������ֵΪʹ֮ɾ���ı�Ԫ���
    struct Paradigm *nextc;     //ָ����һ�Ӿ��ͷ���
    struct Clause *sentence;    //�Ӿ�ͷָ��
}Paradigm;

/*����CNF��ʽ����ͷ������ͣ��洢CNF��ʽ��Ϣ*/
typedef struct Root
{
    int litsize;                //�洢��������
    int parasize;               //�洢�Ӿ�����
    Paradigm *first;            //ָ���һ���Ӿ�
}Root;

/*����ָ���Ӿ�����ͷ����ָ��������ṹ����*/
typedef struct Paraline
{
    Paradigm *claline;          //ָ���Ӿ�����ͷ���Paradigm
    struct Paraline *next;      //ָ����һ������
} Paraline;

/*�������������Ϣ����ṹ����*/
typedef struct LitTrabverse
{
    Paraline *Tra_cla;          //ָ���и������ֻ����ֵ��Ӿ�ͷ��������ͷ���
    Clause *Tra_lit;            //ָ��������ֻ����ֵ����ֽ��
}LitTrabverse;

/*������������ļ�ʱ����Ĵ洢��Ԫ��Ϣ�ṹ����*/
typedef struct sudokusolver
{
    int x;                      //�洢����Ϣ
    int y;                      //�洢����Ϣ
    int z;                      //�洢��Ԫ��Ӧ1��9��ֵ��Ϣ
} sudokusolver;

/*����洢��Ԫ��Ϣ�ı�Ԫ���Ա���ṹ����*/
typedef struct ArgueValue
{
    int Value;                  //��Ԫ����ֵ
    int IsInit;                 //��Ԫ�Ƿ��Ѹ�ֵ
    int Occur_times;            //��Ԫ�������Ӿ��г��ֵ��ܴ���
    LitTrabverse Pos;           //��Ԫ���������ֵ������Ϣ�ṹ
    LitTrabverse Neg;           //��Ԫ���и����ֵ������Ϣ�ṹ
    sudokusolver xyz;           //��������ļ�ʱ����ı�Ԫ��Ϣ
} ArgueValue;


typedef struct
{
    int number;                 //��Ԫ��CNF��ʽ�г��ִ���
    int amount;                 //���ִ���Ϊnumber�Ĳ�ͬ��Ԫ����
}Frequent;
typedef struct
{
    int *amount;                //�Բ�ͬ�Ĵ��������ִ�����ͬ�ı�Ԫ������ͬ����Ŀ
    int totalvariety;           //*amount��ͬ������
} SameFre_AmountList;

typedef struct
{
    int argue;                  //��¼��ֵ��Ϊ1������
    int flag;                   //��¼�Ƿ��Ѿ����Թ�argue�ķ����ֵ���ֵ
} mainstack;                    //�ǵݹ�ʽDPLL�м�¼ÿ����Ϊ1�����ֵ�ջ�ṹ

status CreateParadigm(FILE **fp);       //����CNF��ʽ�ڽ�������Ԫ��
status CreateClause(FILE **fp,Clause **sentence,Paradigm *ClausHead,int first);//�����Ӿ�������������
status DestroyParadigm(Root *r);        //���������������Ա�ṹ
status HasUnitClause(Root *r);          //�ж�CNF��ʽ���Ƿ񻹺��е��Ӿ�
Clause * HasUnitClause_Before(Root *r); //�ж�CNF��ʽ���Ƿ񻹺��е��Ӿ䣨�Ż�ǰ�汾��
status isUnitClause(Paradigm *c);       //�ж�ָ��cָ����Ӿ������Ƿ�Ϊ���Ӿ�����

/*������CNF��ʽ��ȡһ������*/
status FindLiteral1(Root *r);   //ȡÿ��DPLL�����ʽ��Occur_Times��������
status FindLiteral2(Root *r);   //ȡԭ��ʽ��Occur_Times��������
status FindLiteral3(Root *r);   //ȡ�Ӿ��е�һ��flagΪ0������
status FindLiteral4(Root *r);   //ȡValueList�����һ��IsInit=0�ı�Ԫ������
Clause * FindLiteral_Before(Root *r);//������CNF��ʽ��ȡһ�����֣��Ż�ǰ�汾��

status DeleteClause(Root *r,int l);     //ɾ������������l�����е��Ӿ�
status AddClause(Root *r,int l);        //��CNF��ʽ�ڽ������ͷ���ֻ��������l�ĵ��Ӿ�����
status RemoveHeadClaus(Root *r,int l);  //ɾ��CNF��ʽ�ڽ������дӱ�ͷ��ʼ��һ��ֻ��������l�ĵ��Ӿ�����
status DeleteLiteral(Root *r,int l);    //ɾ����������Ϊ-l���Ӿ�������
status RecoverCNF(Root *r,int l);       //�ָ���Ϊ����lΪ��ʱ��CNF��ʽ�ڽ����������Ĳ���
void ParadigmTrabverse(Root *r);        //����CNF��ʽ�ڽ�����
status SaveValue(ArgueValue *ValueList,int solut,int time);//����CNF��ʽ�Ľ⼰���ʱ����Ϣ
status OccurTimeCount(void);               //�����ȡ���ļ��б�Ԫ���ִ�����Ϣ������DPLL�����з��Ѳ��Եı�Ԫѡȡ����

#endif /* cnf_h */
