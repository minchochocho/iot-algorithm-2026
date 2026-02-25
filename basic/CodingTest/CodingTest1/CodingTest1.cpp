// 스택을 사용하여 문자열을 뒤집어 출력하는 소스
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct {
	char stk[MAX];
	int ptr;
}Stack;

void Initialize(Stack* st) {
	st->ptr = 0;
}

int Push(Stack* st,char x) {
	if (st->ptr >= MAX) {
		return -1;
	}
	st->stk[st->ptr] = x;
	st->ptr++;

	return 0;
}

char Pop(Stack* st, char *x) {
	if (st->ptr <= 0) {
		return -1;
	}
	st->ptr--;
	*x = st->stk[st->ptr];

	return *x;
}


int main() {
	Stack st;
	char ps[50];
	char *ps2;

	Initialize(&st);

	printf("문자열을 공백없이 입력해주세요 > "); scanf("%s", ps);

	printf("변경전 문자열 : %s\n", ps);
	for (int i = 0; i < strlen(ps); i++) {
 	Push(&st, ps[i]);
	}
	
	// 수행

	// 결과 출력
	printf("뒤집힌 문자열 : ");
	for (int i = 0; i < strlen(ps); i++) {
		printf("%c", Pop(&st, &ps[i]));
	}
	return 0;
}