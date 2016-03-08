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
}thread;

typedef struct processInfo{
    int processNum;
    int numThreads;
}process;

void parse(FILE * input);

process * processParse(char * input);

thread * threadParse(char * input);

burst * burstParse(char * parse);
