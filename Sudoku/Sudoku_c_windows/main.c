/**
 *  main.c
 *  ����SAT��������Ϸ������
 *
 *  Created by ·껶� on 2021/9/12
 *  Copyright ? 2021 ·껶�. All rights reserved.
 */

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include "cnf.h"
#include "DPLL.h"
#include "Sudoku.h"

extern ArgueValue *ValueList;
extern Root *r;

int main(int argc, const char * argv[]) 
{
    int op=1;
    while (op) 
    {
        system("cls");
        printf("\n");
        printf("-------------------------WELCOME TO THE WORLD!-------------------------\n");
        printf("\t\t\tChoose a progame please.\n");
        printf("-----------------------------------------------------------------------\n");
        printf("   1.Sudoku                 2.SAT                0.exit\n");
        printf("-----------------------------------------------------------------------\n   ");
        scanf("%d",&op);
        switch (op) 
        {
            case 1:
                Sudoku();
                break;
            case 2:
                SAT();
                break;
            case 0:
                printf("  logout\n  saving session...\n  ...copying shared history...\n  ...saving history...truncating history files...\n  ...completed.\n\n");
                break;
            default:
                printf(" Input error !");
                getchar();getchar();
                break;
        }
    }
    system("pause");
    return 0;
}
