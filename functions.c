#include <stdio.h>
#include <stdlib.h>
#include "processStrct.h"

void showqueue(struct Process* queue, int limit)
{
  printf("array members are:\n");
  int i;
  for (i = 0; i < limit; i ++)
    printf("%d- %s %d %d %lld\n", i, queue[i].name,queue[i].startT, queue[i].burstT, queue[i].memNeed);
  printf("end...\n");
}

void showmemory(struct Partition* memory, int limit)
{
  printf("memory blocks: [  \n");
  int i;
  for(i = 0; i < limit; i ++)
    printf("part%d: add: %lld  size: %lld\n", i, memory[i].address, memory[i].size);
  printf("  ] end** \n");
}

void showProcessInf(struct Process p)
{
  printf("process: %s\n", p.name);
  printf("start time: %d && burst time: %d && memory need: %lld\n", p.startT, p.burstT, p.memNeed);
}

void showqueueByname(struct Process* queue, int limit)
{
  printf("members==[   ");
  int i;
  for (i = 0; i < limit; i ++)
    printf("(%s) ", queue[i].name);
  printf("  ]\n");
}
void swap(char* a, char* b)
{
    int size = sizeof(*a);
    char* tmp = (char *) malloc(size);
    int i;
    for (i = 0; i < size; i ++)
        tmp[i] = a[i];
    for (i = 0; i < size; i ++)
        a[i] = b[i];
    for (i = 0; i < size; i ++)
        b[i] = tmp[i];
    free(tmp);
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
			swap((char *)&processArr[i], (char *)&processArr[j]);
		}
	}
	swap((char *)&processArr[i + 1], (char *)&processArr[end]);
	return (i + 1);
}

int quicksort(struct Process* processArr, int start, int end)
{
	if (start < end){
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
	for (i = 0; i < limit; i ++)
		 scanf("%s %d %d %lld", processArr[i].name, &processArr[i].startT, &processArr[i].burstT, &processArr[i].memNeed);
	sortProcessQueuebyStartT(processArr, limit);
	return limit;
}

int FIFOextract(struct Process* excratedP, int witchone, struct Process* queue, int* limit)
{
  if (*limit == 0) return 0;
	int i = witchone;
  for (i; i < *limit - 1; i ++)
    swap((char *)&queue[i], (char *)&queue[i + 1]);
  *excratedP = queue[(*limit)];
  (*limit) --;
  return 1;
}

void FIFOadd(struct Process* p, struct Process* queue, int* limit)
{
  queue[(*limit)] = *p;
  (*limit)++;
}
