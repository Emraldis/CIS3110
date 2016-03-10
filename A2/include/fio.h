	#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Burst {
    int burstNum;
    int CPUTime;
    int IOTime;
    Burst * nextBurst;
};

typedef struct Thread {
    int	threadNum;
    int arrivalTime;
    int numBursts;
    Thread * nextThread;
    Burst * nextBurst;
};

typedef struct Process {
    int processNum;
    int numThreads;
    Process * nextProcess;
    Thread * nextThread;
};

void parse(FILE * input);

void * processParse(char * input);

void * threadParse(char * input);

void * burstParse(char * input);

Process * createProcess(char * input);

Thread * createThread(char * input);

Burst * createBurst(char * burst);
#endif
