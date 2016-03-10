#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct BurstInfo {
    int burstNum;
    int CPUTime;
    int IOTime;
    Burst * nextBurst;
}Burst;

typedef struct ThreadInfo {
    int	threadNum;
    int arrivalTime;
    int numBursts;
    Thread * nextThread;
    Burst * nextBurst;
}Thread;

typedef struct ProcessInfo {
    int processNum;
    int numThreads;
    Process * nextProcess;
    Thread * nextThread;
}Process;

void parse(FILE * input);

void * processParse(char * input);

void * threadParse(char * input);

void * burstParse(char * input);

Process * createProcess(char * input);

Thread * createThread(char * input);

Burst * createBurst(char * burst);
#endif
