#include "fio.h"

void * processParse(char * input){
	
}

void * threadParse(char * input){
	
}

void * burstParse(char * input){
	
}

Process * createProcess(char * input){
    Process * newProcess;
    char * tempString;

    newProcess = malloc(sizeof(Process));

    tempString = strtok(input, " ");
    newProcess->processNum = atoi(tempString);
    tempString = strtok(NULL, " ");
    newProcess->numThreads = atoi(tempString);

    return(newProcess);
}

Thread * createThread(char * input){
    Thread * newThread;

    newThread = malloc(sizeof(Thread));

    return(newThread);
}
