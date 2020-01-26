#include <stdio.h>
#include "functions.h"

/* process struct is defined in header file just for case is here
struct Process
{
	char name[64];
	int startT;
	int burstT;
	int memNeed; // may not have more than int memory
};*/


int sortProcessQueuebyStartT(struct Process New[], int pnum){
	quicksort(New, 0, pnum - 1);
	return 0;
}




int main(){
	struct Process New[1000]; // new queue process
	int pnum = handleInput(New);
	sortProcessQueuebyStartT(New, pnum);
	int i;
	for (i = 0; i < pnum; i ++){
		printf("\n%s %d %d %d", New[i].name,New[i].startT, New[i].burstT, New[i].memNeed);
	}
	
	return 0;
}

