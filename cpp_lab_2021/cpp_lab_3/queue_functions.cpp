#include"def.h"

/// <summary>
/// ��ʼ�����У��������m��Ԫ��
/// </summary>
/// <param name="m"></param>
QUEUE::QUEUE(int m) : elems(new int[m]), max(m), head(0), tail(0) {}

/// <summary>
/// ��q�����ʼ������
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
/// ��q�ƶ���ʼ������
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
/// ���ض��е�ʵ��Ԫ�ظ���
/// </summary>
/// <returns></returns>
QUEUE::operator int() const noexcept {
    return max == 0 ? 0 : (tail + max - head) % max;
}

/// <summary>
/// ���ض�����������Ԫ�ظ���max
/// </summary>
/// <returns></returns>
int QUEUE::size() const noexcept {
    return this->max;
}

/// <summary>
/// ��e�����β���������ص�ǰ����
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
/// �Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
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
/// �����ֵ�����ر���ֵ����
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
/// �ƶ���ֵ�����ر���ֵ����
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
/// ��ӡ������s������s
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
/// ���ٵ�ǰ����
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