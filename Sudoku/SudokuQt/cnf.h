#ifndef CNF_H
#define CNF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qstring.h>
#include <qdebug.h>
#include <qtextcodec.h>
#include <QTextCodec>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define INCREASEMENT 100
#define SUDOKU_LENGTH 9
#define SUDOKU_BOX 729

typedef int status;


/* 定义子句链表结点结构类型 */
typedef struct Clause
{
    int literal;                // 记录子句中的文字
    int flag;                   // 标记该文字是否已被删除，未删除时值为0，否则值为使之删除的变元序号
    struct Clause *nextl;       // 指向该子句中下一文字的指针
    struct Clause *litline;     // 指向整个CNF公式邻接链表中下一个文字相同的子句结点
} Clause;

/* 定义CNF范式链表结点（即子句链表头结点）结构类型 */
typedef struct Paradigm
{
    int number;                 // 子句中显示的文字数
    int flag;                   // 标记该子句是否已被删除，未删除时值为0，否则值为使之删除的变元序号
    struct Paradigm *nextc;     // 指向下一子句的头结点
    struct Clause *sentence;    // 子句头指针
} Paradigm;

/* 定义CNF范式链表头结点类型，存储CNF范式信息 */
typedef struct Root
{
    int litsize;                // 存储文字数量
    int parasize;               // 存储子句数量
    Paradigm *first;            // 指向第一个子句
} Root;

/* 定义指向子句链表头结点的指针链表结点结构类型 */
typedef struct Paraline
{
    Paradigm *claline;          // 指向子句链表头结点Paradigm
    struct Paraline *next;      // 指向下一链表结点
} Paraline;

/* 定义文字相关信息链表结构类型 */
typedef struct LitTrabverse
{
    Paraline *Tra_cla;          // 指向含有该正文字或负文字的子句头结点链表的头结点
    Clause *Tra_lit;            // 指向该正文字或负文字的文字结点
} LitTrabverse;

/* 定义求解数独文件时所需的存储变元信息结构类型 */
typedef struct sudokusolver
{
    int x;                      // 存储行信息
    int y;                      // 存储列信息
    int z;                      // 存储变元对应1～9数值信息
} sudokusolver;

/* 定义存储变元信息的变元线性表结点结构类型 */
typedef struct ArgueValue
{
    int Value;                  // 变元的真值
    int IsInit;                 // 变元是否已赋值
    int Occur_times;            // 变元在所有子句中出现的总次数
    LitTrabverse Pos;           // 变元所有正文字的相关信息结构
    LitTrabverse Neg;           // 变元所有负文字的相关信息结构
    sudokusolver xyz;           // 求解数独文件时所需的变元信息
} ArgueValue;


typedef struct
{
    int number;                 // 变元在CNF范式中出现次数
    int amount;                 // 出现次数为number的不同变元总数
} Frequent;
typedef struct
{
    int *amount;                // 对不同的次数，出现次数相同的变元数量相同的数目
    int totalvariety;           // *amount不同的总数
} SameFre_AmountList;

typedef struct
{
    int argue;                  // 记录真值设为1的文字
    int flag;                   // 记录是否已经测试过argue的反文字的真值
} mainstack;                    // 非递归式DPLL中记录每次设为1的文字的栈结构

status CreateParadigm(FILE **fp);       // 创建CNF范式邻接链表及变元表
status CreateClause(FILE **fp,Clause **sentence,Paradigm *ClausHead,int first); // 创建子句链表及文字链表
status DestroyParadigm(Root *r);        // 销毁所有链表及线性表结构
status HasUnitClause(Root *r);          // 判断CNF范式中是否还含有单子句
Clause * HasUnitClause_Before(Root *r); // 判断CNF范式中是否还含有单子句（优化前版本）
status isUnitClause(Paradigm *c);       // 判断指针c指向的子句链表是否为单子句链表

/* 在整个CNF公式中取一个文字 */
status FindLiteral1(Root *r);           // 取每次DPLL处理后公式中Occur_Times最大的文字
status FindLiteral2(Root *r);           // 取原公式中Occur_Times最大的文字
status FindLiteral3(Root *r);           // 取子句中第一个flag为0的文字
status FindLiteral4(Root *r);           // 取ValueList正序第一个IsInit=0的变元正文字
Clause * FindLiteral_Before(Root *r);   // 在整个CNF公式中取一个文字（优化前版本）

status DeleteClause(Root *r,int l);                           // 删除出现了文字l的所有单子句
status AddClause(Root *r,int l);                              // 在CNF范式邻接链表表头添加只含有文字l的单子句链表
status RemoveHeadClaus(Root *r,int l);                        // 删除CNF范式邻接链表中从表头开始第一个只含有文字l的单子句链表
status DeleteLiteral(Root *r,int l);                          // 删除所有文字为-l的子句链表结点
status RecoverCNF(Root *r,int l);                             // 恢复认为文字l为真时对CNF范式邻接链表所作的操作
QString ParadigmTrabverse(Root *r);                              // 遍历CNF范式邻接链表
status SaveValue(ArgueValue *ValueList,int solut,int time,QString filenameInfo);   // 保存CNF范式的解及求解时间信息
status OccurTimeCount(void);                                  // 处理读取的文件中变元出现次数信息，决策DPLL过程中分裂策略的变元选取策略

#endif // CNF_H
