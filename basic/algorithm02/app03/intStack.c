// intStack.c 스택 자료구조 함수 구현파일

#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include"intStack.h"

/*--- 스택 초기화 ---*/
int Initialize(IntStack* st, int max) {
	st->ptr = 0;	// 스택을 비우고 시작
	if ( (st->stk=calloc(max, sizeof(int))) == NULL ) {	// 동적배열 생성 실패
		st->max = 0;
		return -1;	// 오류리턴
	}
	st->max = max;
	return 0;		// 오류없이 초기화
}

/*--- 스택에 데이터 Push(푸시) ---*/
int Push(IntStack* st, int x) {
	if (st->ptr >= st ->max) {
		return -1;	// 데이터 더 추가불가
	}

	st->stk[st->ptr] = x;	// 이전값 다음에 스택에 데이터추가
	st->ptr++;	// ptr을 나중에 1증가

	return 0;	// 오류없이 실행 종료
}

/*--- 스택에서 데이터 Pop(팝) ---*/
int Pop(IntStack* st, int* x) {
	if (st->ptr <= 0) {
		return -1;	// 오류
	}
	st->ptr--;	// 먼저 ptr 위치값을 1 감소 
	*x = st->stk[st->ptr];
	// st->stk[st->ptr] = 0;

	return 0;
}

/*--- 스택에서 마지막 데이터 Peek(피크) ---*/
int Peek(const IntStack* st, int* x) {
	if (st->ptr <= 0) {
		return -1;	// 오류
	}

	*x = st->stk[st->ptr - 1];	// st->ptr--와는 전혀 다름
	return 0;
}

/*--- 스택 Clear(비우기) ---*/
void Clear(IntStack* st) {
	st->ptr = 0;	// 다음에 데이터를 푸시할 위치를 0으로 바꿈
					// 포인터 배열 사이에 데이터는 남아 있음
}

/*--- 스택 최대용량 ---*/
int Capacity(const IntStack* st) {
	return st->max;

}

/*--- 스택 데이터 개수 ---*/
int Size(const IntStack* st) {
	return st->ptr;
}

/*--- 스택 빈 여부확인 ---*/
int IsEmpty(const IntStack* st) {
	return st->ptr <= 0;	// 1 true 0 false
}

/*--- 스택 만실 여부확인 ---*/
int IsFull(const IntStack* st) {
	return st->ptr >= st->max;
}

/*--- 스택 검색 ---*/
int Search(const IntStack* st, int x) {
	for (int i = st->ptr-1; i >=0 ; i--) {	// 위에서부터 거꾸로 검사
		if (st->stk[i] == x) {
			return i;	// 값이 있는 인덱스를 리턴
		}
	}
	return -1;	// 0번 인덱스에도 데이터가 있기 때문

}


/*--- 스택의 모든 데이터 출력 ---*/
int Print(const IntStack* st) {
	for (int i = 0; i < st->ptr; i++) {
		printf("%d > ", st->stk[i]);
	}
	printf("\n");
}

/*--- 스택 종료 ---*/
void Terminate(IntStack* st) {
	if (st->stk != NULL) {
		free(st->stk);
	}
	st->max = st->ptr = 0;	// x와 ptr을 모두 0으로 릴리즈(해제)
}