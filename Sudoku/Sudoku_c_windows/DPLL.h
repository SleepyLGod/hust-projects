/**
 *  DPLL.h
 *  ����SAT��������Ϸ������
 * 
 *  Created by ·껶� on 2021/9/12
 *  Copyright ? 2021 ·껶�. All rights reserved.
 */

#ifndef DPLL_h
#define DPLL_h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cnf.h"

status SAT(void);
status DPLL1(int num,int op,int times);   //���õ�һ�ֱ�Ԫѡȡ���Եĵݹ��㷨DPLL����
status DPLL2(int num,int op,int times);   //���õڶ��ֱ�Ԫѡȡ���Եĵݹ��㷨DPLL����
status DPLL3(int num,int op,int times);   //���õ����ֱ�Ԫѡȡ���Եĵݹ��㷨DPLL����
status DPLL4(int num,int op,int times);   //���õ����ֱ�Ԫѡȡ���Եĵݹ��㷨DPLL����
status DPLL (int num,int op,int times);   //���õ�һ�ֱ�Ԫѡȡ���Եķǵݹ��㷨DPLL����
status DPLL_Before(Root *r,int op);       //�Ż�ǰ�汾DPLL
void AnswerComplete(void);                //����SAT�����
status AnswerCheck(int solut);            //���SAT�������ȷ��

#endif /* DPLL_h */
