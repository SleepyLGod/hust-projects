#include"def.h"

/// <summary>
/// 矩阵定义
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="r"></param>
/// <param name="c"></param>
template<typename T>
MAT<T>::MAT(int r, int c) : r(r), c(c), e(new T[r * c]) {}

/// <summary>
/// 深拷贝构造
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
template<typename T>
MAT<T>::MAT(const MAT& a) : e(new T[a.r * a.c]), r(a.r), c(a.c) {
	for (int i = 0; i < a.r * a.c; ++i) {
		e[i] = a.e[i];
	}
}

/// <summary>
/// 移动构造
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T>::MAT(MAT&& a) noexcept : e(a.e), r(a.r), c(a.c) {
	*(T*)&(a.c) = 0;
	*(T*)&(a.r) = 0;
	*(T**)&(a.e) = nullptr;
}

/// <summary>
/// 销毁矩阵
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
MAT<T>::~MAT() noexcept {
	if (e != nullptr) {
		delete[] e;
	}
	*(T**)&e = nullptr; // 将剩余变量赋值为0
	*(int*)&r = 0;
	*(int*)&c = 0;
}

/// <summary>
/// 取矩阵r行的第一个元素地址，r越界抛异常
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="r"></param>
/// <returns></returns>
template<typename T>
T* const MAT<T>::operator[] (int r) {
	if (r < this->r && r >= 0) {
		return &e[r * c];
	}else {
		throw("Operator[] ERROR!");
	}
}

/// <summary>
/// 矩阵加法，不能加抛异常
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T> MAT<T>::operator+(const MAT& a) const {
	if (r == a.r && c == a.c) {
		MAT R(r, c);
		int tmp = 0;
		int i = 0;
		for (i = 0; i < r * c; i++){ 
			R.e[i] = e[i] + a.e[i];
		}
		return R;
	}
	throw("Operator+ ERROR!");		 // 抛出异常
}

/// <summary>
/// 矩阵减法，不能减抛异常
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T> MAT<T>::operator-(const MAT& a) const {
	if (r == a.r && c == a.c) {
		MAT R(r, c);
		int i = 0;
		for (i = 0; i < r * c; i++) {
			R.e[i] = e[i] - a.e[i];	// 相减
		}
		return R;
	}
	throw("Operator- ERROR!");		// 抛出异常
}

/// <summary>
/// 矩阵乘法，不能乘抛异常
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T> MAT<T>::operator*(const MAT& a) const {
	if (c == a.r) { // 当this的列数等于a的行数时
		MAT ans(r, a.c);
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < a.c; ++j) {
				ans[i][j] = 0;
				for (int k = 0; k < c; ++k) {
					ans[i][j] = ans[i][j] + e[i * c + k] * a.e[k * c + j];
				}
			}
		}
		return ans;
	}
	throw("Operator* ERROR!");
}

/// <summary>
/// 矩阵转置
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
MAT<T> MAT<T>::operator~() const {
	MAT ans(c, r);
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			ans[j][i] = e[i * c + j];
		}
	}
	return ans;
}

/// <summary>
/// 深拷贝赋值运算
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T>& MAT<T>::operator=(const MAT& a) {
	if (this != &a) {		// 若this和a不相等则进行操作
		if (e != nullptr) { // 如果p中队列不为空
			delete[] e;
		}
		*(T**)&e = new T[r * c];
		for (int i = 0; i < r * c; ++i) {
			e[i] = a.e[i];
		}
		int* tmp;
		tmp = (int*)&r;
		*tmp = a.r;
		tmp = (int*)&c;
		*tmp = a.c;
	}
	return *this;
}

/// <summary>
/// 移动赋值运算
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T>& MAT<T>::operator=(MAT<T>&& a)noexcept {
	if (this != &a)	{		// 若p和q不相等则进行操作
		if (e != nullptr){	// 如果p中队列不为空		
			delete[] e;		// 则释放内存，避免泄露
		}
		*(T**)&e = a.e;		// 进行相应浅拷贝赋值
		*(int*)&r = a.r;
		*(int*)&c = a.c;
		*(T**)&a.e = nullptr;// 将原来结构体赋值为0
		*(int*)&a.r = 0;
		*(int*)&a.c = 0;
		return *this;
	}
}

/// <summary>
/// “+=”运算
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T>& MAT<T>::operator+=(const MAT<T>& a) {
	if (r == a.r && c == a.c) {
		int i = 0;
		for (i = 0; i < r * c; ++i) {
			e[i] += a.e[i];
		}
		if (i == r * c) {		// 检查循环是否完整结束
			return *this;
		}
	}
	throw("Operator+= ERROR!"); // 抛出异常
}

/// <summary>
/// “-=”运算
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T>& MAT<T>::operator-=(const MAT<T>& a) {
	if (r == a.r && c == a.c) {
		int i = 0;
		for (i = 0; i < r * c; i++)	{
			e[i] -= a.e[i];
		}
		if (i == r * c) {		// 检查循环是否完整结束
			return *this;
		}
	}
	throw("Operator-= ERROR!");	// 抛出异常
 }

/// <summary>
/// “*=”运算
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T>& MAT<T>::operator*=(const MAT<T>& a) {
	if (c == a.r) {
		MAT ans(r, a.c);
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < a.c; ++j) {
				ans[i][j] = 0;
				for (int k = 0; k < c; ++k) {
					ans[i][j] = ans[i][j] + e[i * c + k] * a.e[k * c + j];
				}
			}
		}
		(*this) = ans;
		return *this;
	}
	throw("Operator*= ERROR!");
}

/// <summary>
/// print输出至s并返回s：列用空格隔开，行用回车结束
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="s"></param>
/// <returns></returns>
template<typename T>
char* MAT<T>::print(char* s)const noexcept {
	int n = 0;
	if (typeid(e[0]) == typeid(int)) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (j != 0) {
					n += sprintf(s + n, "%c", ' ');
				}
				n += sprintf(s + n, "%6ld", e[i * c + j]);
				if (j == c - 1) {
					n += sprintf(s + n, "%c", '\n');
				}
			}
		}
	} else if (typeid(e[0]) == typeid(long)) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (j != 0) {
					n += sprintf(s + n, "%c", ' ');
				}
				n += sprintf(s + n, "%6lld", e[i * c + j]);
				if (j == c - 1) {
					n += sprintf(s + n, "%c", '\n');
				}
			}
		}
	} else if (typeid(e[0]) == typeid(float)) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (j != 0) {
					n += sprintf(s + n, "%c", ' ');
				}
				n += sprintf(s + n, "%8f", e[i * c + j]);
				if (j == c - 1) {
					n += sprintf(s + n, "%c", '\n');
				}
			}
		}
	} else if (typeid(e[0]) == typeid(double)) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (j != 0) {
					n += sprintf(s + n, "%c", ' ');
				}
				n += sprintf(s + n, "%8lf", e[i * c + j]);
				if (j == c - 1) {
					n += sprintf(s + n, "%c", '\n');
				}
			}
		}
	}
	s[n] = '\0';
	printf("%s", s);
	return s;
 }