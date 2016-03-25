#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include <stdlib.h>

typedef struct Process{
	int memoryReq;
	struct Process next;
	char * label;
}prc;
typedef struct Memory{
	int totalSize;
	int blockSize;
	struct Process ** memoryArr;
}mem;
typedef struct Disk{
	struct Process * prcList;
	struct Process * last;
}dsk;
#endif