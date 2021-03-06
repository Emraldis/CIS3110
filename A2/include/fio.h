#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct BurstInfo {
    int burstNum;
	int threadNum;
	int processNum;
    int CPUTime;
    int IOTime;
	int readyTime;
	int entryTime;
	int exitTime;
	int remainingTime;
    struct BurstInfo * nextBurst;
}Burst;

typedef struct ThreadInfo {
    int	threadNum;
	int processNum;
    int arrivalTime;
    int numBursts;
	int waitTime;
	int turnaroundTime;
	int serviceTime;
	int IOTime;
	int finishTime;
    struct ThreadInfo * nextThread;
    struct BurstInfo * nextBurst;
}Thread;

typedef struct ProcessInfo {
    int processNum;
    int numThreads;
	int complete;
    struct ProcessInfo * nextProcess;
    struct ThreadInfo * nextThread;
}Process;

Process * createProcess(char * input);

Thread * createThread(char * input,int processNum);

Burst * createBurst(char * burst,int processNum);
#endif
