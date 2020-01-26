#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

struct Process
{
	char name[64];
	int startT;
	int burstT;
	int memNeed; // lesser than 8G available ram
};

void swap(struct Process* a, struct Process* b)
{
	struct Process tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(struct Process New[], int start, int end){
	int pivot = New[end].startT;
	int i = (start - 1);
	int j;
	for (j = start; j <= end - 1; j ++)
	{
		if (New[j].startT < pivot)
		{
			i++;
			swap(&New[i], &New[j]);
		}
	}
	swap(&New[i + 1], &New[end]);
	return (i + 1);
}

int quicksort(struct Process New[], int start, int end){
	if (start < end)
	{
		int pivot = partition(New, start, end);
		quicksort(New, start, pivot - 1);
		quicksort(New, pivot + 1, end);
	}
}
int handleInput(struct Process New[]){
	int pnum;
	scanf("%d", &pnum);
	int i = 0;
	for (i; i < pnum; i ++){
		 scanf("%s %d %d %d", New[i].name, &New[i].startT, &New[i].burstT, &New[i].memNeed);
	}
	return pnum;
}
void * exitPQueue(void * queue, int pnum){
	struct Process* queue = (struct Process) * queue;
	void * exited = (void)* 
}

#endif
