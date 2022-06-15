#include <stdio.h>
#include <stdlib.h>   

int  a[5] = { 1, 2, 3, 4, 5 };
short x = 100;
short y = -32700;  // 注意观察初始值较大带来的问题
int  psub;
int sum(int a[], int length) {
	int i;
	int result = 0;
	for (i = 0; i < length; i++) {
		result += a[i];
	}
	return result;
}


/*
在32位系统中，int的范围是-2147483648~+2147483647，
而unsigned int的范围是0~4294967295
90000000H == 2415919104
*/
int main(int argc, char* argv[]) {
	short z;
	char str[10] = "The end!";
	z = sum(a, 0x90000000);
	printf("sum : %d \n", z);
	if (x > y) {
		printf("condition1:  %d > %d \n", x, y);
	} else {
		printf("condition1:  %d < %d \n", x, y);
	}
	z = x - y;
	printf("condition2: (%d) - (%d) = %d \n", x, y, z);
	psub = &x - &y;
	if (psub < 0) {
		printf("condition3: & %d < & %d \n", x, y);
	}
	printf(str);
	return 0;
}

