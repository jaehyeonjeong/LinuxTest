//덧셈, 곱셈표
#include <stdio.h>

//x1과 x2의 함을 구합니다.
int sum(int x1, int x2)
{
	return x1 + x2;
}

//x1과 x2의 곱을 구합니다.
int mul(int x1, int x2)
{
	return x1 * x2;
}

//표 출력
void kuku(int(*calc)(int, int)) //함수 포인터 사용
{
	int i, j;
	for(i = 1; i <= 9; i++){
		for(j = 1; j <= 9; j++)
			printf("%3d", (*calc)(i, j)); //호출 함수는 프로그램이 실행될 때 결정됩니다.
		putchar('\n');
	}
}

int main(void)
{
	puts("덧셈표");
	kuku(sum);
	puts("\n곱셈표");
	kuku(mul);

	return 0;
}
