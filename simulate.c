#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "functions.h"

const int MAXPROCESS = 100;
const long long int MAXMEMSIZE =  8589934592;	 /* 8GB */

void allocateMemory(int bestfit, struct Process* p, struct Partition* Memory, int* Mlim)
{
	struct Partition busy;
	struct Partition loose;
	int i;
	busy.size = p->memNeed;
	busy.address = Memory[bestfit].address;
	busy.status = 'B';
	p->allocation = busy.address;
	if (Memory[bestfit].size - p->memNeed == 0){
		Memory[bestfit] = busy;
	}else{
		// other size there will be a over head partition
		loose.size = Memory[bestfit].size - p->memNeed;
		loose.address = Memory[bestfit].address + p->memNeed;
		loose.status = 'F';
		Memory[bestfit] = busy;
		Memory[(*Mlim)++] = loose;
		for (i = *Mlim - 1; i > bestfit + 1; i --)
			swapPartition(&Memory[i], &Memory[i - 1]);
	}
}
int memoryAvailable(struct Process* p, struct Partition* Memory, int Mlim)
{
	int bestfit = -1;
	long long int bestsize = MAXMEMSIZE;
	int i;
	for (i = 0; i < Mlim; i ++){ // for all free partitions in partition memory table
		if (Memory[i].status == 'F' && p->memNeed <= Memory[i].size)
			if (Memory[i].size <= bestsize){ // here is allocation best fit policy
				bestfit = i;
				bestsize = Memory[i].size;
			}
	}
	return bestfit;
}

void uniteBelowPartitions(int index, struct Partition* Memory, int* Mlim)
{

	if (Memory[index + 1].status == 'F'){
		int i;
		Memory[index].size += Memory[index + 1].size;
		for (i = index + 1; i < *Mlim - 1; i ++){
			 	swapPartition(&Memory[i], &Memory[i + 1]);
	 	}
 		(*Mlim)--;
		if (index + 1 < *Mlim)
			uniteBelowPartitions(index, Memory, Mlim);
	}
}

void deallocateMemory(struct Process* p, struct Partition* Memory, int* Mlim)
{
	int index;
	for (index = 0; index < *Mlim; index++)
		if (Memory[index].address == p->allocation)
			break;
	p->allocation = -1;
	Memory[index].status = 'F';
	// now that the partition is free memory manager must unite every partition that are neighbours
	while(index > 0 && Memory[index - 1].status == 'F') index --;
	uniteBelowPartitions(index, Memory, Mlim);
}

void checkBlockedes(int globtimer, struct Process* Block, int* Blim, struct Process* Ready, int* Rlim,
							 struct Partition* Memory, int* Mlim)
{
	// to do : before check just sort block to order by memory need
	int i;
	long long int result;
	int cont;
	struct Process survive;
	for (i = 0; i < *Blim; i ++){
		result = memoryAvailable(&Block[i], Memory, *Mlim);
		if (result != -1){
			cont = FIFOextract(&survive, i, Block, Blim);
			i--;
			allocateMemory(result, &survive, Memory, Mlim);
			printf(" ** blocked process %s has been re allocated to %lld\n", survive.name, result);
			printf("%s %d %llx %llx\n", survive.name, globtimer, survive.allocation, (survive.allocation + survive.memNeed - 1));
			FIFOadd(&survive, Ready, Rlim);
			showmemory(Memory, *Mlim);
		}
	}

}

void checkNewCommers(int globtimer, struct Process* New, int *Nlim, struct Process* Ready, int* Rlim,
	 									struct Partition* Memory, int* Mlim, struct Process* Block, int* Blim)
{
	int i = 0;
	int result;
	struct Process tmp;
	while (i < *Nlim){
		result = -1;
		if (New[i].startT <= globtimer){
			printf("%dms: prcess %s arrived ...\n", globtimer, New[i].name);
			result = memoryAvailable(&New[i], Memory, *Mlim);
			if (result == -1){
				printf("				... and it has blocked\n");
				FIFOextract(&tmp, 0, New, Nlim);
				FIFOadd(&tmp, Block, Blim);
			} else{
				printf("				... and allocated to %lld\n", Memory[result].address);
				FIFOextract(&tmp, 0, New, Nlim);
				allocateMemory(result, &tmp, Memory, Mlim);
				printf("%s %d %llx %llx\n", tmp.name, globtimer, tmp.allocation, (tmp.allocation + tmp.memNeed - 1));
				FIFOadd(&tmp, Ready, Rlim);
				showmemory(Memory, *Mlim);
			}
		}
		else
			break;
	}
}

int initMemory(struct Partition* memory)
{
	int limit = 1;
	memory[0].address = 0;
	memory[0].size = MAXMEMSIZE; // maximom size of memory
	memory[0].status = 'F';
	printf("memory initated with one partition of size: %lld\n", memory[0].size);
	return limit;
}

void checkio(int time, struct Process* IO, int* Ilim, struct Process* Block, int* Blim,
							struct Process* Ready, int* Rlim)
{
	int i;
	struct Process tmp;
	for (i = 0; i < Ilim; i ++){
		if (time >= IO[i].waiting){
			FIFOextract(&tmp, i, IO, Ilim);
			i--;
			tmp.waiting = 0;
			if (tmp.swaped == 1){
				// means process is blocked
				FIFOadd(&tmp, Block, Blim);
			} else{
				// means process is not blocked yet
				FIFOadd(&tmp, Ready, Rlim);
			}
		} else{
			IO[i].waiting -= time;
		}
	}
}

int main()
{
	int quantum = 50;
	struct Process New[MAXPROCESS]; // new queue process
	int Nlim = sortAreadinp(New); // returns sorted processes by start time
	struct Process Ready[MAXPROCESS];
	int Rlim = 0;
	struct Process Terminate[MAXPROCESS];
	int Tlim = 0;
	struct Partition Memory[MAXPROCESS];
	int Mlim = initMemory(Memory);
	struct Process Block[MAXPROCESS];
	int Blim = 0;
	struct Process IO[MAXPROCESS];
	int Ilim = 0;

	int globtimer = New[0].startT;
	checkNewCommers(globtimer, New, &Nlim, Ready, &Rlim,
									Memory, &Mlim, Block, &Blim);
	struct Process running;

	printf("NEW ");showqueue(New, Nlim);
	printf("READY ");showqueue(Ready, Rlim);
	printf("BLOCK ");showqueue(Block, Blim);
	// showmemory(Memory, Mlim);

	int cont;
	printf("[***] scheduler started\n\n");
	if (Rlim > 0) while(7999) // round rabin scheduler
	{
		// printf("ready queue: ");showqueueByname(Ready, Rlim);
		// printf("block queue: ");showqueueByname(Block, Blim);
		cont = FIFOextract(&running, 0, Ready, &Rlim);
		// process consumes cpu
		if (cont == 0){
			while(Rlim == 0 && Blim == 0)){
				if (Nlim == 0 && Ilim == 0) break;
				globtimer++
				checkNewCommers(globtimer, New, &Nlim, Ready, &Rlim,
												Memory, &Mlim, Block, &Blim);
				checkio(1, IO, &Ilim, Block, &Blim, Ready, &Rlim);
			}
			if (Blim > 0)
				checkBlockedes(globtimer, Block, &Blim, Ready, &Rlim, Memory, &Mlim);

		}
		else if (running.burstT >= quantum){
			globtimer += quantum;
			running.burstT -= quantum;
			FIFOadd(&running, Ready, &Rlim);
			if (Ilim > 0)
				checkio(quantum, IO, &Ilim, Block, &Blim, Ready, &Rlim);
			// printf("%dms: %s take %dms and remained: %d ...\n", globtimer, running.name, quantum, running.burstT);
		} else{
			globtimer += running.burstT;
			// terminate process
			if (Ilim > 0)
				checkio(running.burstT, IO, &Ilim, Block, &Blim, Ready, &Rlim);
			if (running.waiting == 0){
				printf("%dms: %s  terminated...\n", globtimer, running.name);
				deallocateMemory(&running, Memory, &Mlim); ///
				FIFOadd(&running, Terminate, &Tlim);
				/// after dealocating memory there is a chance for blocked processes
				// showmemory(Memory, Mlim);
			} else{
				running.burstT = running.waiting;
				running.waiting = running.waiting / 5;
				if (Blim > 0){
					printf("%dms: %s has been swaped for IO... \n", globtimer, running.name);
					deallocateMemory(&running, Memory, &Mlim); ///
					running.swaped = 1;
				} else {
					printf("%dms: %s is waiting for IO... \n", globtimer, running.name);
					running.swaped = 0;
				}
				FIFOadd(&running, IO, &Ilim);
			}

			if (Blim > 0)
				checkBlockedes(globtimer, Block, &Blim, Ready, &Rlim, Memory, &Mlim);

		}
		checkNewCommers(globtimer, New, &Nlim, Ready, &Rlim,
										Memory, &Mlim, Block, &Blim);
		if (Nlim == 0 && Rlim == 0 && Ilim == 0) break; // means no process will ever come
	}
	printf("\n[**] scheduling ended...\n");

	showmemory(Memory, Mlim);
	printf("NEW ");showqueue(New, Nlim);
	printf("READY ");showqueue(Ready, Rlim);
	printf("TERMINATE ");showqueue(Terminate, Tlim);
	return 0;
}
