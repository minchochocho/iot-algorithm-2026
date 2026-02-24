// app05 - 재귀 알고리즘 비재귀로 변경
// goto문은 되도록 사용하지 말 것 << 제일 옛날 방식

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include "intStack.h"

/*--- 재귀함수 호출부분 제거 ---*/

void recur(int n) {
	IntStack stk;	// 스택 추가
	Initialize(&stk, 100);

Top:	//
	if (n > 0) {
		//recur(n - 1);	// 머리재귀 제거
		Push(&stk, n);	// n값을 스택에 푸시
		n -= 1;
		goto Top;
	}
	if (!IsEmpty(&stk)) {	// 스택이 비어있지 않으면
		Pop(&stk, &n);		// 임시 저장한 n값 팝
		printf("%d\n", n);	
		
		//recur(n - 2);	// 꼬리재귀 제거
		n = n - 2;
		goto Top;
	}
	Terminate(&stk);
}


int main() {
	int i = 0;

start:	// 라벨, 앵커(돛)
	printf("i = %d\n", i);
	i++;

	if (i < 5) goto start;	// start 라벨로 점프

	printf("끝!\n");

	return 0;
}
