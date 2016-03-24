#include <stdio.h>
#include <stdlib.h>

typedef struct Process{
	int memoryReq;
	char * label;
}prc;
typedef struct Memory{
	int totalSize;
	int blockSize;
	struct Process ** memoryArr;
}mem;
typedef struct Disk{
	struct Process ** diskMem;
}dsk;