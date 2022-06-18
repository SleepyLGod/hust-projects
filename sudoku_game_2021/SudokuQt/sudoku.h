#define SUDOKU_H

/**
 *  Suduku.h
 *  基于SAT的数独游戏求解程序
 *
 *  Created by 路昊东 on 2021/9/5
 *  Copyright ? 2021 路昊东. All rights reserved.
**/

#ifndef Sudoku_h
#define Sudoku_h

#include <stdio.h>
#include <stdlib.h>
#include "dpll.h"
#include "cnf.h"

extern int sudoku_table[9][9];          //定义全局变量int类型二维数组存储数独盘
extern int users_sudoku[9][9];          //存储输出的含空格数独问题格局

status Sudoku(void);
FILE * CreateSudokuFile(void);          //创建数独问题转化为SAT问题后的cnf文件
status CreateSudoku(void);              //创建新的随机9*9数独终盘
status DigHole(int num);                //对已知数独终盘挖num个洞生成有唯一解的数独问题
status SudokuComplete(void);            //完善数独终盘
status SudokuExchange(void);            //基于cell元素交换原理增加一数独终盘的随机性
status CNFSudokuTableTransform(void);   //数独对应SAT变元表转化为二维数组
status SudokuTablePrint(void);          //输出数独盘

#endif /* Sudoku_h */
