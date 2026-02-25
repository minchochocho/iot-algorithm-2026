// 카드가 한장 남을때까지
// 버리기, 맨아래로 옮기기 반복
// 큐 이용
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int max;
	int num;
	int front;
	int rear;
	int* que;

}IntQ;

int Init(IntQ* qu, int max) {
	qu->num = qu->front = qu->rear = 0;
	if ((qu->que=calloc(max,sizeof(int))) == NULL) {
		qu->max = 0;
		return -1;
	}
	qu->max = max;
	return 0;
}

int Enque(IntQ* qu, int x) {
	if (qu->num >= qu->max) {
		return -1;
	}
	else {
		qu->num++;
		qu->que[qu->rear] = x;
		qu->rear++;
		if (qu->rear == qu->max) {
			qu->rear = 0;
		}
	}
}

int Deque(IntQ* qu, int* x) {
	if (qu->num <= 0) {
		return -1;
	}
	else {
		qu->num--;	// 큐에서 데이터가 하나 빠질꺼니까
		*x = qu->que[qu->front];
		qu->front++;


		if (qu->front == qu->max) {	// deque를 계속해서 배열 마지막까지 도달
			qu->front = 0;
		}
		return x;
	}

}

int IsOne(const IntQ * qu){
	return qu->num == 1;
}

int Peek(const IntQ* qu, int* x) {
	if (qu->num<=0) {
		return -1;
	}*x = qu->que[qu->front];
	return 0;
}

void Print(const IntQ* qu) {
	printf("%d", qu->que[qu->front]);
}

int main() {
	IntQ que;
	if (Init(&que,8)==-1) {
		puts("큐 생성 실패!");
		exit(1);
	}

	int num,x,cnt=0;

	printf("정수 입력 > "); scanf("%d", &num);

	for (int i = 0; i < num; i++) {
		Enque(&que, i);
	}

	while (1) {
		if (IsOne(&que)) {
			break;
		}
		Deque(&que, &x);
		cnt++;
		if (cnt%2==1) {
			Enque(&que, x);
		}
	}
	Print(&que);
	return 0;
}