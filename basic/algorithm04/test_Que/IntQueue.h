// IntQueue 헤더파일
#ifndef _INTQUEUE_H_
#define _INTQUEUE_H_

typedef struct {
	int max;	// 최대크기
	int num;	// 현재 요소 개수
	int front;	// 큐의 front
	int rear;	// rear
	int* que;	// 큐 맨앞 포인터
} IntQueue;



#endif // !_INTQUEUE_H_
