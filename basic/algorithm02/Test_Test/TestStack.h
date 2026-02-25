// 이름 지정
#ifndef _INTSTACK_H_
#define _INTSTACK_H_

// 스택 구현 구조체
typedef struct {
	int max;	// 용량
	int ptr;	// 포인터
	int* stk;	// 첫요소에 대한 포인터
}IntStack;

// 스택 초기화
int Initialize(IntStack* st, int max);

// 푸시
int Push(IntStack* st, int x);

// 팝 >> 결과는 x로 돌려받음
int Pop(IntStack* st, int* x);

// 피크 >> 집는것 뿐이니깐 변하면 X > const
int Peek(const IntStack* st, int* x);

// Clear
void Clear(IntStack* st);

// 최대용량 캐퍼시티
int Capacity(const IntStack* st);

// 데이터 개수
int Size(const IntStack* st);

// 비었는지
int isEmpty(const IntStack* st);

// 찼는지
int isFull(const IntStack* st);

// 검색
int Search(const IntStack* st, int x);

// 출력
int Print(const IntStack* st);

// 종료
void Terminate(IntStack* st);

#endif // !_INTSTACK_H_
