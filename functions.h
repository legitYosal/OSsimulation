#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include "processStrct.h"
void showqueue(struct Process* queue, int limit);
void showProcessInf(struct Process p);
void showqueueByname(struct Process* queue, int limit);
void swap(char* a, char* b);
void showmemory(struct Partition* memory, int limit);
int sortAreadinp(struct Process* processArr);
int FIFOextract(struct Process* excratedP, int witchone, struct Process* queue, int* limit);
void FIFOadd(struct Process* p, struct Process* queue, int* limit);

#endif
