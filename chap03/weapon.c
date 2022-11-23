#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bubble(int n)
{
	int i, j, tmp;
	int* a = (int*)malloc(sizeof(int)*n);
	memset(a, 0, sizeof(int) * n);
	for(i = 0; i < n; i++)
	{
		printf("a[%d] = ", i);
		scanf("%d", &a[i]);
	}

	for(j = 0; j < n; j++){
		for(i = 0; i < (n - 1) - j; i++){
			if(a[i] < a[i + 1]){
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
			}
		}
	}
	for(i = 0; i < n; i++){
		printf("a[%d] = %d\n", i, a[i]);
	}

	return a[0];
	free(a);
}

int main()
{
	int x, y, i, j, n;
	printf("y값을 입력하세요 : ");
	scanf("%d", &y);

	printf("x값을 입력하세요 : ");
	scanf("%d", &x);
	

	int** matrix = (int**)malloc(sizeof(int) * y);
	for(i = 0; i < y; i++)
		*matrix = (int*)malloc(sizeof(int) * x);

	for(j = 0; j < y; j++){
		for(i = 0; i < x; i++){
			printf("[y][x] = [%d][%d] = %d\n", j, i, i + j);
		}
	}
	
	printf("n의 값을 입력하세요 : ");
	scanf("%d", &n);
	printf("%d\n", bubble(n));

	free(matrix);
	return 0;
}
