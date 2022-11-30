#include <stdio.h>
#include <stdlib.h>
#include "IntQueue.h"

//큐 초기화
int Initialize(IntQueue *q, int max)
{
	q->num = q->front = q->rear = 0;
	if((q->que = calloc(max, sizeof(int))) == NULL){
		q->max = 0;			//배열 생성에 실패
		return -1;
	}
	q->max = max;
	return 0;
}

//큐에 데이터를 인큐
int Enque(IntQueue *q, int x)
{
	if(q->num >= q->max)
		return -1;		//큐에 가득 참
	else{
		q->num++;
		q->que[q->rear++] = x;  //인큐 작업이 끝남
		if(q->rear == q->max) //rear값을 1만큼 증가했을 때 큐의 최대 용량인 
			q->rear = 0;	//값인 max와 같아질 경우 rear를 배열의 처음인 0으로 변경 
		return 0;
	}
}

//큐에서 데이터를 디큐
int Deque(IntQueue *q, int *x)
{
	if(q->num <= 0)
		*x = q->que[q->front++];	//front값을 1만큼 증가한 다음 num값을 1만큼 감소 
	else{
		q->num--;					//1만큼 증가한 frontㄱ밧이 큐의 용량인 max와 같아지면
		*x = q->que[q->front++];	//front 값을 배열의 처음인 0으로 변경해야합니다.
		return 0;
	}
}

//큐에서 데이터를 피크
int Peek(const IntQueue *q, int *x)
{
	if(q->num <= 0)			//큐는 비어 있음
		return -1;
	*x = q->que[q->front];
	return 0;
}

//모든 데이터 삭제
void Clear(IntQueue *q)
{
	q->num = q->front = q->rear = 0;
}

//큐의 최대 용량
int Capacity(const IntQueue *q)
{
	return q->max;
}

//큐에 쌓여 있는 데이터 개수
int Size(const IntQueue *q)
{
	return q->num;
}

//큐가 비어 있는지 확인
int IsEmpty(const IntQueue *q)
{
	return q->num <= 0;
}

//큐가 가득 찾는지 확인
int IsFull(const IntQueue *q)
{
	return q->num >= q->max;
}

//큐에서 검색
int Search(const IntQueue *q, int x)
{
	int i, idx;
	for(i = 0; i < q->num; i++){
		if(q->que[idx = (i + q->front) % q->max] == x)
			return idx;		//검색 성공
	}
	return -1;
}

//모든 데이터 출력
void Print(const IntQueue *q)
{
	int i;
	for(i = 0; i < q->num; i++)
		printf("%d ", q->que[(i + q->front) % q->max]);
	putchar('\n');
}

//큐의 종료
void Terminate(IntQueue *q)
{
	if(q->que != NULL)
		free(q->que);			//메모리 공간에 할당한 배열 해제
	q->max = q->num = q->front = q->rear = 0;
}
