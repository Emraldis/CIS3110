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

Process * createProcess(char * input, FILE * inputFile);

Thread * createThread(char * input, FILE * inputFile);

Burst * createBurst(char * burst);
#endif
