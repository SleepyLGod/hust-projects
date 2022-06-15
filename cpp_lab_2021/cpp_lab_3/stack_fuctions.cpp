#include "def.h"

/// <summary>
/// 初始化栈：最多存放2m-2个元素
/// </summary>
/// <param name="m"></param>
STACK::STACK(int m) : QUEUE(m), q(m) {}

/// <summary>
/// 用栈s深拷贝初始化栈
/// </summary>
/// <param name="s"></param>
STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {}

/// <summary>
/// 用栈s移动拷贝初始化栈
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK::STACK(STACK&&s) noexcept :QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {}

/// <summary>
/// 返回栈的容量即2m
/// </summary>
/// <returns></returns>
int STACK::size() const noexcept {
	return QUEUE::size() + q.size();
}

/// <summary>
/// 返回栈的实际元素个数
/// </summary>
/// <returns></returns>
STACK:: operator int() const noexcept {
	return QUEUE::operator int() + q.operator int();
}

/// <summary>
/// 将e入栈，并返回当前栈
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
/// 从队首出元素到e，并返回当前队列
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
/// 深拷贝赋值并返回被赋值队列
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK& STACK::operator=(const STACK& s) {
	QUEUE::operator=(s);
	q.operator=(s.q);
	return *this;
}

/// <summary>
/// 移动赋值并返回被赋值栈
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
STACK& STACK::operator=(STACK&& s) noexcept {
    QUEUE::operator=((QUEUE&&)s);
    q.operator=((QUEUE&&)s.q);
    return *this;
}

/// <summary>
/// 从栈底到栈顶打印栈元素 
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
/// 销毁栈
/// </summary>
/// <returns></returns>
STACK::~STACK() noexcept {
    QUEUE::~QUEUE();
    q.~QUEUE();
}