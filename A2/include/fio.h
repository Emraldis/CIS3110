#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct BurstInfo {
    int burstNum;
    int CPUTime;
    int IOTime;
    struct BurstInfo * nextBurst;
}Burst;

typedef struct ThreadInfo {
    int	threadNum;
    int arrivalTime;
    int numBursts;
    struct ThreadInfo * nextThread;
    struct BurstInfo * nextBurst;
}Thread;

typedef struct ProcessInfo {
    int processNum;
    int numThreads;
    struct ProcessInfo * nextProcess;
    struct ThreadInfo * nextThread;
}Process;

void * processParse(char * input);

void * threadParse(char * input);

void * burstParse(char * input);

Process * createProcess(char * input);

Thread * createThread(char * input);

Burst * createBurst(char * burst);
#endif
