#ifndef PROCESSSTRUCT_HEADER
#define PROCESSSTRUCT_HEADER
struct Process
{
	char name[64];
	int startT;
	int burstT;
	int memNeed; // lesser than 8G available ram
};
#endif
