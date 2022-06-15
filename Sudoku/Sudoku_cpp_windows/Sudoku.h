/**
 *  Suduku.h
 *  ����SAT��������Ϸ������
 * 
 *  Created by ·껶� on 2021/9/5
 *  Copyright ? 2021 ·껶�. All rights reserved.
**/

#ifndef Sudoku_h
#define Sudoku_h

#include <stdio.h>
#include <stdlib.h>
#include "DPLL.h"
#include "cnf.h"

status Sudoku(void);
FILE * CreateSudokuFile(void);  //������������ת��ΪSAT������cnf�ļ�
status CreateSudoku(void);      //�����µ����9*9��������
status SolveSudoku(void);       //�������cnf�ļ���ת��Ϊ����������ʽ���
status DigHole(int num);        //����֪����������num����������Ψһ�����������
status SudokuComplete(void);    //������������
status SudokuExchange(void);    //����cellԪ�ؽ���ԭ������һ�������̵������
status CNFSudokuTableTransform(void);//������ӦSAT��Ԫ��ת��Ϊ��ά����
status SudokuTablePrint(void);  //���������

#endif /* Sudoku_h */
