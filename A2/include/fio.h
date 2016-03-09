#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include <string.h>

typedef struct burstInfo{
    int burstNum;
    int CPUTime;
    int IOTime;
    burst * next;
}burst;

typedef struct threadInfo{
    int	threadNum;
    int arrivalTime;
    int numBursts;
    thread * nextThread;
    burst * nextBurst;
}thread;

typedef struct processInfo{
    int processNum;
    int numThreads;
    process * nextProcess;
    thread* nextThread;
}process;

void parse(FILE * input);

void * processParse(char * input);

void * threadParse(char * input);

void * burstParse(char * parse);

process* createProcess();
#endif
