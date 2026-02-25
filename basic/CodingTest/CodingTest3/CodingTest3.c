// 정수 n 재귀함수 출력 소스
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

unsigned long long fact(int n) {
	if (n > 0) {
		return(unsigned long long)n * fact(n - 1);
	}
	else {
		return 1;
	}
}

int main() {
	int x = 0;
	unsigned long long result;
	printf("정수 입력 > "); scanf("%d", &x);

	result = fact(x);
	printf("%d! = %llu\n", x, result);

	return 0;
}