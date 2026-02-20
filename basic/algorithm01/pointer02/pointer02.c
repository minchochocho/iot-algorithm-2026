// pointer 02 - 함수와 포인터

#include<stdio.h>

void change(int*);

int main() {
	int num = 10;

	change(&num);
	printf("변경된 num : %d\n", num);

	return 0;
}

void change(int* p) {
	*p = 300;	// 원래 있던 10이 300으로 바뀜

}

// 일반 변수의 전달은 복사
// 포인터의 전달은 `원본 조작`
// 임베디드에서 매우 중요 << 용량을 줄일수 있음