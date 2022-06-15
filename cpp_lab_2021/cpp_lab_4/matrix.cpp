#include"def.h"

/// <summary>
/// ������
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="r"></param>
/// <param name="c"></param>
template<typename T>
MAT<T>::MAT(int r, int c) : r(r), c(c), e(new T[r * c]) {}

/// <summary>
/// �������
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
/// �ƶ�����
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
/// ���پ���
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
MAT<T>::~MAT() noexcept {
	if (e != nullptr) {
		delete[] e;
	}
	*(T**)&e = nullptr; // ��ʣ�������ֵΪ0
	*(int*)&r = 0;
	*(int*)&c = 0;
}

/// <summary>
/// ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
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
/// ����ӷ������ܼ����쳣
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
	throw("Operator+ ERROR!");		 // �׳��쳣
}

/// <summary>
/// ������������ܼ����쳣
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
			R.e[i] = e[i] - a.e[i];	// ���
		}
		return R;
	}
	throw("Operator- ERROR!");		// �׳��쳣
}

/// <summary>
/// ����˷������ܳ����쳣
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T> MAT<T>::operator*(const MAT& a) const {
	if (c == a.r) { // ��this����������a������ʱ
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
/// ����ת��
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
/// �����ֵ����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T>& MAT<T>::operator=(const MAT& a) {
	if (this != &a) {		// ��this��a���������в���
		if (e != nullptr) { // ���p�ж��в�Ϊ��
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
/// �ƶ���ֵ����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a"></param>
/// <returns></returns>
template<typename T>
MAT<T>& MAT<T>::operator=(MAT<T>&& a)noexcept {
	if (this != &a)	{		// ��p��q���������в���
		if (e != nullptr){	// ���p�ж��в�Ϊ��		
			delete[] e;		// ���ͷ��ڴ棬����й¶
		}
		*(T**)&e = a.e;		// ������Ӧǳ������ֵ
		*(int*)&r = a.r;
		*(int*)&c = a.c;
		*(T**)&a.e = nullptr;// ��ԭ���ṹ�帳ֵΪ0
		*(int*)&a.r = 0;
		*(int*)&a.c = 0;
		return *this;
	}
}

/// <summary>
/// ��+=������
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
		if (i == r * c) {		// ���ѭ���Ƿ���������
			return *this;
		}
	}
	throw("Operator+= ERROR!"); // �׳��쳣
}

/// <summary>
/// ��-=������
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
		if (i == r * c) {		// ���ѭ���Ƿ���������
			return *this;
		}
	}
	throw("Operator-= ERROR!");	// �׳��쳣
 }

/// <summary>
/// ��*=������
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
/// print�����s������s�����ÿո���������ûس�����
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