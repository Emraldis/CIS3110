#include "fio.h"

void * processParse(char * input){
	
}

void * threadParse(char * input){
	
}

void * burstParse(char * input){
	
}

Process * createProcess(char * input){
    Process newProcess;
    char * tempString;

    newProcess = malloc(sizeof(Process));

    tempString = strtok(input, " ");
    newProcess.processNum = atoi(tempString);
    tempString = strtok(input, " ");
    newProcess.numThreads = atoi(tempString);

    return(newProcess);
}
