#pragma once
#ifndef __DEF_H__
#define __DEF_H__
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

struct Queue {
    int* const elems;   // elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const int max;	  	// elems��������Ԫ�ظ���max
    int head, tail;	 	// ����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
};

void initQueue(Queue* const p, int m);	                // ��ʼ��pָ���У��������m��Ԫ��
void initQueue(Queue* const p, const Queue& s);         // ��s�����ʼ��pָ����
void initQueue(Queue* const p, Queue&& s);              // ��s�ƶ���ʼ��pָ����
int  number(const Queue* const p);	                    // ����pָ���е�ʵ��Ԫ�ظ���
int  size(const Queue* const p);			            // ����pָ������������Ԫ�ظ���max
Queue* const enter(Queue* const p, int e);              // ��e�����β����������p
Queue* const leave(Queue* const p, int& e);             // �Ӷ��׳�Ԫ�ص�e��������p
Queue* const assign(Queue* const p, const Queue& q);    // �����s�����в�����p
Queue* const assign(Queue* const p, Queue&& q);         // �ƶ���s�����в�����p
char* print(const Queue* const p, char* s);             // ��ӡpָ������s������s
void destroyQueue(Queue* const p);	                    // ����pָ��Ķ���

#endif // !__DEF_H__
