// app01 - 큐 구현
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"IntQueue.h"

int main() {
	IntQueue que;
	if (Initialize(&que,8)== -1) {
		puts("큐 생성 실패!");
		return 1; // exit(1);
	}

	int menu, x, ch;

	while (1) {
		menu = -1;	// 빼지 말 것

		printf("현재 데이터 수 : %d / %d \n", Size(&que), Capacity(&que));
		printf("(1)인큐, (2)디큐, (3)피크, (4)출력, (5)검색, (6)초기화, (0) 종료 > "); scanf("%d", &menu);

		// 잘못된 키보드 입력 버퍼를 제거
		while ((ch = getchar()) != '\n' && ch != EOF) { }

		if (menu==0) {
			break;
		}

		switch (menu) {
		case 1:	// 인큐
			if(IsFull(&que)){
				puts("\a오류 : 큐가 가득 찼습니다");
			}
			//if (Enque(&que,x) == -1)
			else {
				printf("데이터 입력 > "); scanf("%d", &x);
				Enque(&que, x);
				printf("인큐 데이터 : %d\n", x);
			}
			break;

		case 2:	// 디큐
			if (IsEmpty(&que))
				puts("\a오류 : 큐가 비어 있습니다");
			else{
				Deque(&que, &x);
				printf("디큐 데이터 : %d\n", x);
			}
			break;

		case 3:	// 피크
			if (Peek(&que,&x) == -1) {
				puts("\a오류 : 피크 실패");
			}
			else {
				printf("피크 데이터 : %d\n", x);
			}
			break;

		case 4:	// 출력
			Print(&que);
			break;

		case 5:	// 검색
			printf("찾을 데이터 입력 > "); scanf("%d", &x);
			{
				int idx = Search(&que, x);
				if (idx==-1) {
					puts("\a오류 : 해당 데이터가 큐에 없습니다.");
				}
				else
					printf("데이터 %d는 큐의 %d번째 인덱스에 있습니다.\n", x, idx);
			}
			break;

		case 6:	// 초기화
			Clear(&que);
			break;
		
		}
	}
	Terminate(&que);
	return 0;
}