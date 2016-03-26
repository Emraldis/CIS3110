#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include <stdlib.h>

typedef struct ProcessInfo{
	int memoryReq;
	struct ProcessInfo * next;
	char * label;
	int cycle;
	int age;
	int version;
}Process;
typedef struct MemoryInfo{
	int totalSize;
	int blockSize;
	struct ProcessInfo ** memoryArr;
}Memory;
typedef struct DiskInfo{
	struct ProcessInfo * prcList;
	struct ProcessInfo * last;
}Disk;
typedef struct Stats{
	int numHoles;
	int numProcesses;
	int loads;
	int cumulativeHoles;
	int cumulativeProcesses;
	float cumulativeMem;
	float avgProcesses;
	float avgHoles;
	float percentMem;
	float avgMem;
	
}Stat;
#endif