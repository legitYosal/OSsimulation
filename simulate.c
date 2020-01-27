#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "functions.h"


void checkNewCommers(int globtimer, struct Process* New, int *Nlim, struct Process* Ready, int* Rlim)
{
	int i = 0;
	while (i < *Nlim)
		if (New[i].startT < globtimer + 1){
			printf("prcess %s has arrived...\n", New[i].name);
			FIFOadd((struct Process*)FIFOextract(0, New, Nlim), Ready, Rlim);
		}
		else
			break;
}

int main(){
	int quantum = 50;
	struct Process New[100]; // new queue process
	int Nlim = sortAreadinp(New); // returns sorted processes by start time
	struct Process Ready[100];
	int Rlim = 0;
	struct Process Terminate[100];
	int Tlim = 0;
	int globtimer = New[0].startT;
	checkNewCommers(globtimer, New, &Nlim, Ready, &Rlim);
	int turn = 0;
	struct Process running;

	showqueue(New, Nlim);
	showqueue(Ready, Rlim);

	printf("[***] scheduler started\n\n");
	if (Rlim > 0) while(7999) // round rabin scheduler
	{
		running = Ready[turn];
		// process consumes cpu
		if (running.burstT > quantum + 1){
			globtimer += quantum;
			printf("%d: %s take %dms and continued...\n", globtimer, running.name, quantum);
			running.burstT -= quantum;
		} else{
			globtimer += running.burstT;
			printf("%d: %s take %dms and terminated...\n", globtimer, running.name, running.burstT);
			// terminate process
			FIFOadd((struct Process*) FIFOextract(turn, Ready, &Rlim), Terminate, &Tlim);
			turn --;
		}
		printf("debug tool: ready queue: ");
		showqueueByname(Ready, Rlim);
		usleep(100000);
		checkNewCommers(globtimer, New, &Nlim, Ready, &Rlim);
		if (Nlim == 0 && Rlim == 0) break;
		turn = (turn + 1) % Rlim;
	}
	printf("\n[**] scheduling ended...\n");

	showqueue(New, Nlim);
	showqueue(Ready, Rlim);
	showqueue(Terminate, Tlim);
	return 0;
}
