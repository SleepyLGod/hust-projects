#include "def.h"

int main(int argc, char* argv[]) {
	MAT<int>   a(1, 2), b(2, 2), c(1, 2);
	char t[2048];
	a[0][0] = 1;							// 类似地初始化矩阵的所有元素
	a[0][1] = 2; 							// 等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
	a.print(t);								// 初始化矩阵后输出该矩阵
	b[0][0] = 3; 	b[0][1] = 4;			// 调用T* const operator[ ](int r)初始化数组元素
	b[1][0] = 5; 	b[1][1] = 6;
	b.print(t);
	c = a * b;								// 测试矩阵乘法运算
	c.print(t);
	(a + c).print(t);						// 测试矩阵加法运算
	c = c - a;								// 测试矩阵减法运算
	c.print(t);
	c += a;									// 测试矩阵“+=”运算
	c.print(t);
	c = ~a;									// 测试矩阵转置运算
	c.print(t);
	extern const char* TestMAT(int& s);		// 引入测试函数
	int nMark = 0;							// 记录分数
	const char* strResult = TestMAT(nMark);	// 记录提示语句
	cout << strResult << endl;
	cout << nMark << endl;
	return 0;
}