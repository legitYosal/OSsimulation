#ifndef PROCESSSTRUCT_HEADER
#define PROCESSSTRUCT_HEADER
struct Process
{
	char name[32];
	int startT;
	int burstT;
	long int memNeed; // lesser than 8G available ram
  struct Partition* allocation;
};
struct Partition
{
  long int size;
  long int address;
  struct Process* access;
  char status; // B stands for busy && F stands for free
}
#endif
