// pointer 03 - 배열과 포인터의 관계

#include<stdio.h>

int main() {
	int ary[] = { 10,30,50,70,90 };
	int* pa = ary;	// 배열변수의 요소 [] 를 빼면 배열변수의 시작주소를 뜻함
	int cnt = sizeof(ary) / sizeof(ary[0]);	// 20byte / 4byte => 5(배열 크기)

	for (int i = 0; i < cnt; i++) {
		printf("ary[%d] = %d\n", i, *(pa + i));	// == ary[i]
	}
	return 0;
}

// 배열 이름 = 첫번째 요소 주소
// pa + 1 은 1바이트가 아님! 자료형 크기만큼 1 이동
// ary[i] == *(ary + i) == *(pa + i)