// app06 - 이전 소수계산해서 나누기 횟수가 78022번
// 합성수로는 나눌 필요가 없으므로 나누기를 줄일 수 있음
// 이 소스로 실행하면 나누기 횟수가 14622번으로 줄였음 => 소수로만 나누기
// 최적화를 하여 1804회까지 줄였음 => 홀수 + 제곱근까지만 계산
// 메모리 사용량 : 기존 2020 + 4(is_prime) = 2,024 bytes

#include<stdio.h>

int main() {
	int prime[500];		// 이전 계산한 소수를 저장하는 배열
	int prime_cnt = 0;		// 소수의 개수
	unsigned long counter = 0;

	prime[prime_cnt++] = 2;	// 2는 소수

	for (int n = 3; n <=1000; n+=2) {
		int i;
		int is_prime=1;	// 소수라고 가정

		//for ( i = 1; i < prime_cnt; i++) {
		// 나누는 소수의 제곱이 n보다 작거나 같을 때 까지만
		for (i = 1; i < prime_cnt&&(prime[i]* prime[i]<=n); i++) {
			counter++;
			if (n % prime[i]==0) {	// 소수가 아님
				is_prime = 0;
				break;
			}
		}

		if (is_prime) {
			prime[prime_cnt++] = n;		// 마지막까지 나누어지지 않으면 소수배열 저장
		}
	}

	// 출력은 따로
	for (int i = 0; i < prime_cnt; i++) {
		printf("%d\n", prime[i]);
		if ((i + 1) % 10 == 0) printf("\n"); // 10개씩 줄바꿈
	}

	printf("1~1000사이 소수 개수 : %d\n", prime_cnt);
	printf("나눗셈 실행 횟수 : %d", counter);

	return 0;
}