#include"def.h"

/// <summary>
/// 初始化队列：最多申请m个元素
/// </summary>
/// <param name="m"></param>
QUEUE::QUEUE(int m) : elems(new int[m]), max(m), head(0), tail(0) {}

/// <summary>
/// 用q深拷贝初始化队列
/// </summary>
/// <param name="q"></param>
QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), max(q.max) {
    this->head = q.head;
    this->tail = q.tail;
    for (int i = q.head; i != q.tail; i = (i + 1) % max) {
        this->elems[i] = q.elems[i];
    }
}

/// <summary>
/// 用q移动初始化队列
/// </summary>
/// <param name="q"></param>
/// <returns></returns>
QUEUE::QUEUE(QUEUE&& q) noexcept :elems(q.elems), max(q.max) {
    this->head = q.head;
    this->tail = q.tail;
    for (int i = q.head; i != q.tail; i = (i + 1) % max) {
        this->elems[i] = q.elems[i];
    }
    q.head = 0;
    q.tail = 0;
    *(int**)&(q.elems) = nullptr;
    *(int*)&(q.max) = 0;
}

/// <summary>
/// 返回队列的实际元素个数
/// </summary>
/// <returns></returns>
QUEUE::operator int() const noexcept {
    return max == 0 ? 0 : (tail + max - head) % max;
}

/// <summary>
/// 返回队列申请的最大元素个数max
/// </summary>
/// <returns></returns>
int QUEUE::size() const noexcept {
    return this->max;
}

/// <summary>
/// 将e入队列尾部，并返回当前队列
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
QUEUE& QUEUE::operator<<(int e) {
    if ((tail + 1) % max == head) {
        throw "QUEUE is full!";
        return *this;
    }
    this->elems[tail] = e;
    this->tail = (tail + 1) % max;
    return *this;
}

/// <summary>
/// 从队首出元素到e，并返回当前队列
/// </summary>
/// <param name="e"></param>
/// <returns></returns>
QUEUE& QUEUE::operator>> (int& e) {
    if (this->tail == this->head) {
        throw "QUEUE is empty!";
        return *this;
    }
    e = this->elems[head];
    head = (head + 1) % max;
    return *this;
}

/// <summary>
/// 深拷贝赋值并返回被赋值队列
/// </summary>
/// <param name="q"></param>
/// <returns></returns>
QUEUE& QUEUE::operator=(const QUEUE& q) {
    if (this->elems == q.elems) return *this;
    if (this->elems != nullptr) {
        delete[] this->elems;
    }
    *(int**)&(this->elems) = new int[q.max];
    *(int*)&(this->max) = q.max;
    this->head = q.head; 
    this->tail = q.tail;
    for (int i = q.head; i <= q.tail; i++) {
        this->elems[i % q.max] = q.elems[i % q.max];
    }
    return *this;
}

/// <summary>
/// 移动赋值并返回被赋值队列
/// </summary>
/// <param name="q"></param>
/// <returns></returns>
QUEUE& QUEUE::operator=(QUEUE&& q) noexcept {
    if (this->elems == q.elems) return *this;
    if (this->elems != nullptr) {
        delete[] this->elems;
    }
    *(int**)&(this->elems) = q.elems; 
    this->head = q.head;
    this->tail = q.tail;
    for (int i = q.head; i <= q.tail; i++) {
        this->elems[i % q.max] = q.elems[i % q.max];
    }
    q.head = 0;
    q.tail = 0;
    *(int**)&(q.elems) = nullptr;
    *(int*)&(q.max) = 0;
    return *this;
}

/// <summary>
/// 打印队列至s并返回s
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
char* QUEUE::print(char* s) const noexcept {
    char a[10];
    int i;
    s[0] = 0;
    for (i = this->head; i != tail; i = (i + 1) % max) {
        sprintf(a, "%d,", this->elems[i]);
        strcat(s, a);
    }
    return s;
}

/// <summary>
/// 销毁当前队列
/// </summary>
QUEUE::~QUEUE() {
    if (this->elems != nullptr) {
        delete[] this->elems;
        this->head = 0;
        this->tail = 0;
        *(int**)&(this->elems) = nullptr;
        *(int*)&(this->max) = 0;
    }
}