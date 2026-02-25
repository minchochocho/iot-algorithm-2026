// 최고점수 학생 이름 성적 출력
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

typedef struct {
	int num[50];
	char name[50][10];
}student;

int main() {
	student st;
	int best;
	int best_score;
	char best_name[10];
	int x;
	char p[50];

	printf("입력 > "); scanf("%d", &x);

	for (int i = 0; i < x; i++) {
		scanf("%s %d", &st.name[i], &st.num[i]);
	}
	best_score = st.num[0];
	strcpy(best_name, st.name[0]);

	for (int i = 1; i < x; i++) {
		if (st.num[i] > best_score) {
			best_score = st.num[i];
			strcpy(best_name, st.name[i]);
		}
	}
	printf("출력 > %s %d",best_name,best_score);

	return 0;

}