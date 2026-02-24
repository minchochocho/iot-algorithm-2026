// app03 - 스택 구현

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"intStack.h"


int main() {
	IntStack st;
	
	// 스택 초기화
	if (Initialize(&st, 10) == -1) {
		puts("스택 초기화 실패!");
		return 1;	// exit(1);
	}

	int menu, x, ch;

	while (1) {	// 무한루프
		// 스택 기능 구현
		menu = -1;
		printf("현재 데이터수 : %d / %d\n", Size(&st), Capacity(&st));
		printf("(1)푸시, (2)팝, (3)피크, (4)출력, (0)종료 > "); scanf("%d", &menu);

		// 잘못된 키보드 입력 버퍼를 제거
		// 기초 프로그래밍 주소록 토이프로젝트 소스 참조
		while ((ch = getchar()) != '\n' && ch != EOF) { }

		if (menu == 0) break;	// 종료 처리

		switch (menu) {
		case 1:	// 푸시
			printf("데이터 입력 > "); scanf("%d", &x);

			if (Push(&st, x) == -1) {
				puts("\a오류 : 푸시 실패!");
			}
			break;
		case 2:	// 팝
			if (IsEmpty(&st)==1) {
				puts("스택이 비어있습니다!");

			}
			else if (Pop(&st,&x) == -1) {
				puts("\a오류 : 팝 실패!");
			}
			else {
				printf("팝 데이터는 %d\n", x);
			}
			break;
		case 3:	// 피크
			if (Peek(&st,&x) == -1) {
				puts("\a오류 : 피크 실패!");
			}
			else {
				printf("피크 데이터는 %d\n",x);
			}
			break;
		case 4:	// 출력
			Print(&st);
			break;
		case 5:	// 검색
			printf("%검색할 수 입력 > "); scanf("%d", &x);
			int res = Search(&st, x);
			if (res== -1) {
				printf("검색 실패");
			}else
				printf("검색 결과 : stack[%d] => %d\n", res, st.stk[res]);
			break;
		}

	}

	Terminate(&st);

	return 0;
}