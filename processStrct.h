#ifndef PROCESSSTRUCT_HEADER
#define PROCESSSTRUCT_HEADER
struct Process
{
	char name[32];
	int startT;
	int burstT;
	long long int memNeed; // lesser than 8G available ram
  struct Partition* allocation;
};
struct Partition
{
  long long int size;
  long long int address;
  char status; // B stands for busy && F stands for free
};
#endif
