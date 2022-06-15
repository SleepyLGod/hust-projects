#include "def.h"

/// <summary>
/// ��ʼ��ջ�������2m-2��Ԫ��
/// </summary>
/// <param name="m"></param>
STACK::STACK(int m) : QUEUE(m), q(m) {}

/// <summary>
/// ��ջs�����ʼ��ջ
/// </summary>
/// <param name="s"></param>
STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {}

/// <summary>
/// ��ջs�ƶ�������ʼ��ջ
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK::STACK(STACK&&s) noexcept :QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {}

/// <summary>
/// ����ջ��������2m
/// </summary>
/// <returns></returns>
int STACK::size() const noexcept {
	return QUEUE::size() + q.size();
}

/// <summary>
/// ����ջ��ʵ��Ԫ�ظ���
/// </summary>
/// <returns></returns>
STACK:: operator int() const noexcept {
	return QUEUE::operator int() + q.operator int();
}

/// <summary>
/// ��e��ջ�������ص�ǰջ
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
STACK& STACK::operator<<(int e) {
    if (QUEUE::operator int() < QUEUE::size() - 1) {
        QUEUE::operator<<(e);
        return *this;
    } else if (q.operator int() < q.size() - 1) {
        int tmp = 0;
        QUEUE::operator>>(tmp);
        q.operator<<(tmp);
        QUEUE::operator<<(e);
        return *this;
    } else {
        throw("STACK is full!");
    }
}

/// <summary>
/// �Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
STACK& STACK::operator>>(int& e) {
    if (QUEUE::operator int()) {
        int sizebase = QUEUE::operator int();
        int tmp = 0;
        for (int i = 0; i < sizebase - 1; i++) {
            QUEUE::operator>>(tmp);
            QUEUE::operator<<(tmp);
        }
        QUEUE::operator>>(e);
        return *this;
    } else if (q.operator int()) {
        int sizebase = q.operator int(), tmp = 0;
        for (int i = 0; i < sizebase - 1; i++) {
            q.operator>>(tmp);
            q.operator<<(tmp);
        }
        q.operator>>(e);
        return *this;
    } else {
        throw("STACK is empty!");
    }
}

/// <summary>
/// �����ֵ�����ر���ֵ����
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK& STACK::operator=(const STACK& s) {
	QUEUE::operator=(s);
	q.operator=(s.q);
	return *this;
}

/// <summary>
/// �ƶ���ֵ�����ر���ֵջ
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK& STACK::operator=(STACK&& s) noexcept {
    QUEUE::operator=((QUEUE&&)s);
    q.operator=((QUEUE&&)s.q);
    return *this;
}

/// <summary>
/// ��ջ�׵�ջ����ӡջԪ�� 
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
char* STACK::print(char* b) const noexcept {
    char* s = (char*)malloc(sizeof(char) * size());
    s = QUEUE::print(s);
    b = q.print(b);
    strcat(b, s);
    delete[] s;
    return b;
}

/// <summary>
/// ����ջ
/// </summary>
/// <returns></returns>
STACK::~STACK() noexcept {
    QUEUE::~QUEUE();
    q.~QUEUE();
}