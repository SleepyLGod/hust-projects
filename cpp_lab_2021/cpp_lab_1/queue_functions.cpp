#include"def.h"

/// <summary>
/// 初始化队列
/// </summary>
/// <param name="p">队列</param>
/// <param name="m">最多申请的元素数量</param>
void initQueue(Queue* const p, int m){ 
	if (m <= 0) { // 不合法！
		throw"Wrong argument";
	}
	if (p->elems){ // 若p已存在，释放原内存防止内存泄漏
		*(int*)&p->max = 0;
		free(p->elems);
		*(int**)&p->elems = nullptr;
	}
	*(int**)&p->elems = (int*)malloc(m * sizeof(int));
	*(int*)&p->max = m;
	p->head = p->tail = 0;
}	

/// <summary>
/// 深拷贝初始化队列
/// </summary>
/// <param name="p">目标队列</param>
/// <param name="s">源队列</param>
void initQueue(Queue* const p, const Queue& s){ 
	if (p->elems){ // 若p已存在，释放原内存防止内存泄漏
		*(int*)&p->max = 0;
		free(p->elems);
		*(int**)&p->elems = nullptr;
	}
	*(int*)&p->max = s.max;
	*(int**)&p->elems = (int*)malloc(p->max * sizeof(int));
	p->head = s.head;
	p->tail = s.tail;
	int i;
	for (i = 0; i < p->max; i++){
		p->elems[i] = s.elems[i];
	}
}

/// <summary>
/// 用s移动初始化p指队列
/// </summary>
/// <param name="p">目标队列</param>
/// <param name="s">源</param>
void initQueue(Queue* const p, Queue&& s){
	if (p->elems){ // 若p已存在，释放原内存防止内存泄漏
		*(int*)&p->max = 0;
		free(p->elems);
		*(int**)&p->elems = nullptr;
	}
	*(int*)&p->max = s.max;
	*(int**)&p->elems = s.elems;
	p->head = s.head;
	p->tail = s.tail;
	*(int**)&s.elems = nullptr;
	*(int*)&s.max = 0;
	s.head = s.tail = 0;
}

/// <summary>
/// 返回p指队列的实际元素个数
/// </summary>
/// <param name="p">队列</param>
/// <returns>元素个数</returns>
int  number(const Queue* const p) { 
	return p->tail >= p->head ? p->tail - p->head : p->tail + p->max - p->head;
}

/// <summary>
/// 返回p指队列申请的最大元素个数max
/// </summary>
/// <param name="p"></param>
/// <returns></returns>
int  size(const Queue* const p){ 
	return p->max;
}

/// <summary>
/// 将e入队列尾部，并返回p
/// </summary>
/// <param name="p"></param>
/// <param name="e"></param>
/// <returns></returns>
Queue* const enter(Queue* const p, int e){ 
	if ((p->tail + 1) % p->max == p->head) {
		throw "Queue is full!";
	}
	else{
		p->elems[p->tail] = e;
		p->tail = (p->tail + 1) % p->max;
		return p;
	}
}

/// <summary>
/// 从队首出元素到e，并返回p
/// </summary>
/// <param name="p"></param>
/// <param name="e"></param>
/// <returns></returns>
Queue* const leave(Queue* const p, int& e){ 
	if (p->head == p->tail)
	{
		throw "Queue is empty!";
	}
	else
	{
		e = p->elems[p->head];
		p->head = (p->head + 1) % p->max;
		return p;
	}
}

/// <summary>
/// 深拷贝赋s给队列并返回p
/// </summary>
/// <param name="p"></param>
/// <param name="q"></param>
/// <returns></returns>
Queue* const assign(Queue* const p, const Queue& q){ 
	if (p == &q) {
		return p;
	}
	if (p->elems && p->elems != q.elems) {
		free(p->elems);
		*(int**)&p->elems = nullptr;
	}
	*(int**)&p->elems = (int*)malloc(q.max * sizeof(int));
	*(int*)&p->max = q.max;
	int i;
	for (i = 0; i < p->max; i++) {
		p->elems[i] = q.elems[i];
	}
	p->head = q.head;
	p->tail = q.tail;
	return p;
}

/// <summary>
/// 移动赋s给队列并返回p
/// </summary>
/// <param name="p"></param>
/// <param name="q"></param>
/// <returns></returns>
Queue* const assign(Queue* const p, Queue&& q){ 
	if (p == &q) {
		return p;
	}
	if (p->elems && p->elems != q.elems) {
		free(p->elems);
		*(int**)&p->elems = nullptr;
	}
	*(int**)&p->elems = q.elems;
	*(int*)&p->max = q.max;
	p->head = q.head;
	p->tail = q.tail;
	*(int**)&q.elems = nullptr;
	*(int*)&q.max = 0;
	q.head = q.tail = 0;
	return p;
}

/// <summary>
/// 打印p指队列至s并返回s
/// </summary>
/// <param name="p"></param>
/// <param name="s"></param>
/// <returns></returns>
char* print(const struct Queue* const p, char* s) { 
	int m = p->max;
	for (int i = p->head; i != p->tail; i = (i + 1) % m) {
		char* location = s + strlen(s);
		sprintf(location, "%d,", p->elems[i]);
	}
	return s;
}

/// <summary>
/// 销毁p指向的队列
/// </summary>
/// <param name="p"></param>
void destroyQueue(Queue* const p){ 
	if (p->elems) {
		free(p->elems);
		*(int**)&p->elems = nullptr;
	}
	*(int*)&p->max = 0;
	p->head = p->tail = 0;
}
