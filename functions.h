#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include "processStrct.h"
void swap(char* a, char* b);
int sortAreadinp(struct Process* processArr);
void showqueue(struct Process* queue, int limit);
void showProcessInf(struct Process p);
void FIFOadd(struct Process* p, struct Process* queue, int* limit);
void* FIFOextract(int witchone, struct Process* queue, int* limit);
void showqueueByname(struct Process* queue, int limit);

#endif
