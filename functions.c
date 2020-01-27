#include <stdio.h>
#include <stdlib.h>
#include "processStrct.h"

void showqueue(struct Process* queue, int limit)
{
  printf("process array members are:\n");
  int i;
  for (i = 0; i < limit; i ++)
    printf("%d- %s %d %d %d\n", i, queue[i].name,queue[i].startT, queue[i].burstT, queue[i].memNeed);
}

void showProcessInf(struct Process p)
{
  printf("process: %s\n", p.name);
  printf("start time: %d && burst time: %d && memory need: %d\n", p.startT, p.burstT, p.memNeed);
}

void swap(struct Process* a, struct Process* b)
{
	struct Process tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(struct Process* processArr, int start, int end)
{
	int pivot = processArr[end].startT;
	int i = (start - 1);
	int j;
	for (j = start; j <= end - 1; j ++)
	{
		if (processArr[j].startT < pivot)
		{
			i++;
			swap(&processArr[i], &processArr[j]);
		}
	}
	swap(&processArr[i + 1], &processArr[end]);
	return (i + 1);
}

int quicksort(struct Process* processArr, int start, int end)
{
	if (start < end)
	{
		int pivot = partition(processArr, start, end);
		quicksort(processArr, start, pivot - 1);
		quicksort(processArr, pivot + 1, end);
	}
}

int sortProcessQueuebyStartT(struct Process* processArr, int limit)
{
	quicksort(processArr, 0, limit - 1);
	return 0;
}

int sortAreadinp(struct Process* processArr)
{
	int limit;
	scanf("%d", &limit);
	int i;
	for (i = 0; i < limit; i ++){
		 scanf("%s %d %d %d", processArr[i].name, &processArr[i].startT, &processArr[i].burstT, &processArr[i].memNeed);
	}
	sortProcessQueuebyStartT(processArr, limit);
	return limit;
}

void* FIFOextract(int witchone, struct Process* queue, int* limit)
{
	int i = witchone;
  for (i = 0; i < *limit - 1; i ++)
    swap(&queue[i], &queue[i + 1]);
  return (void*) &queue[--(*limit)];
}

void FIFOadd(struct Process* p, struct Process* queue, int* limit)
{
  queue[(*limit)++] = *p;
}
