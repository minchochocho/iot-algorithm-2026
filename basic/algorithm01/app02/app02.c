// p22. 중앙값

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

int median3(int a, int b, int c) {
	if (a>=b) {
		if (b>=c) {
			return b;
		}
		else if(a<=c) {
			return a;
		}
		
	}else if(a > c) {
		return a;
	}
	else if (b > c) {
		return c;
	}
	else {
		return b;
	}
}

int main() {
	int a, b, c;

	printf("세 정수 입력\n");
	printf(" a > "); scanf("%d", &a);
	printf(" b > "); scanf("%d", &b);
	printf(" c > "); scanf("%d", &c);

	printf("중앙값은 %d\n", median3(a, b, c));

	return 0;
}