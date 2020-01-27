#include <stdio.h>
#include "functions.h"


int main(){
	struct Process New[1000]; // new queue process
	int Nlim = sortAreadinp(New); // returns sorted processes by start time
	struct Process Ready[1000];
	int Rlim = 0;
	int globtimer = New[0].startT;
	showqueue(New, Nlim);
	showProcessInf(*(struct Process*) FIFOextract(New, Nlim))
	showqueue(New, Nlim);
	return 0;
}
