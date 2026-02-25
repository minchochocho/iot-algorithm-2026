#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"TestStack.h"

int main() {
	IntStack st;

	if (Initialize(&st,10)==-1) {
		puts("스택 초기화 실패");
		return 1;	//exit(1);
	}

	int menu, x, ch;

	while (1) {
		menu = -1;
		printf("현재 데이터 수 : %d/%d\n",Size(&st),Capacity(&st));
		printf("(1)푸시, (2)팝, (3)피크, (4)출력, (0)종료 > "); scanf("%d", &menu);
	
		while ((ch = getchar()) != '\n' && ch != EOF) { }

		if (menu==0) {
			break;
		}
		
		switch (menu) {
		case 1:	// 푸시
			printf("데이터 입력 > "); scanf("%d", &x);
			if (Push(&st,x) == -1) {
				puts("\a오류 : 푸시 실패");
			}
			break;

		case 2:
			if (isEmpty(&st)==1) {
				puts("")
			}

		}
	
	}


	return 0;
}