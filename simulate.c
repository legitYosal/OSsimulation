#include <stdio.h>
#include "functions.h"


void checkNewCommers(int globtimer, struct Process New[], int *Nlim, struct Process Ready, int* Rlim)
{
	int i = 0;
	while (i < *Nlim)
		if (New[i].startT < globtimer + 1)
			FIFOadd(*(struct Process*)FIFOextract(0, New, Nlim), Ready, Rlim);
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
	while(7999) // round rabin scheduler
	{
		running = Ready[turn];
		// process consumes cpu
		if (running.burstT > quantum + 1){
			printf("%s take %dms and continued...\n", running.name, quantum);
			running.burstT -= quantum;
			globtimer += quantum;
		} else{
			printf("%s take %dms and terminated...\n", running.name, running.burstT);
			// terminate process
			globtimer += running.burstT;
			FIFOadd(*(struct Process*) FIFOextract(turn, Ready, &Rlim), Terminate, &Tlim);
			turn --;
		}

		checkNewCommers(globtimer, New, &Nlim, Ready, &Rlim);
		if (Rlim == 0) break;
		turn = (turn + 1) % Rlim;
	}
	prinft("\n[**] scheduling ended...\n");

	showqueue(New, Nlim);
	showqueue(Ready, Nlim);
	showqueue(Terminate, Tlim);
	return 0;
}
