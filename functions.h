#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include "processStrct.h"
void showqueue(struct Process* queue, int limit);
void showProcessInf(struct Process p);
void showqueueByname(struct Process* queue, int limit);
void swap(char* a, char* b);
int sortAreadinp(struct Process* processArr);
void* FIFOextract(int witchone, struct Process* queue, int* limit);
void FIFOadd(struct Process* p, struct Process* queue, int* limit);

#endif
