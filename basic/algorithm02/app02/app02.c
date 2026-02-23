// app02 - 이진검색

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

int bin_search(const int[], int, int);

int main() {
	int nx, ky;

	puts("이진 검색");
	printf("요소 개수 > "); scanf("%d", &nx);
	int* x = calloc(nx, sizeof(int));

	printf("오름차순으로 입력할 것.\n");
	// 첫번째 요소만 먼저 입력
	printf("x[0] > "); scanf("%d", &x[0]);
	for (int i = 1; i < nx; i++) {
		do {
			//int i = ntf("x[%d] : ",i);

			printf("x[%d] : ",i); scanf("%d", &x[i]);
		} while (x[i] < x[i - 1]);	// 배열의 앞의 값이 뒤의 값보다 작으면 안됨
	}	// 중요!!! - 제대로된 입력이 될때까지 반복하는 로직! << 실무에서도 쓸수있는 괜찮은 기능

	// 검색 시작
	printf("검색 값 :"); scanf("%d", &ky);
	int idx = bin_search(x, nx, ky);
	if (idx==-1) {
		puts("검색에 실패했습니다.");
	}
	else { printf("%d는(은) x[%d]에 있습니다. \n", ky, idx); }
	free(x);


	return 0;
}

// n개 요소 배열에서 key와 일치하는 요소 이진검색 함수!
int bin_search(const int a[], int n, int key) {
	int pl = 0;		// 검색범위 맨 앞 인덱스
	int pr = n - 1;	// 검색범위 맨 끝 인덱스

	do {
		int pc = (pl + pr) / 2;	// 검색 범위 중앙 인덱스 << 핵심
		if (a[pc] == key)		// 찾은 인덱스
			return pc;
		else if (a[pc] < key)	// 찾는 값은 중앙값의 오른쪽부분
			pl = pc + 1;		// 검색 범위를 뒤쪽 절반으로 줄이겠다
		else					// 찾는 값은 중앙값의 왼쪽부분
			pr = pc - 1;		// 검색 범위를 앞쪽 절반으로 줄임
	} while (pl<=pr);	// 이진검색에서 pl은 무조건 pr보다 왼쪽에 존재해야함

	return -1;	// 검색 실패
}