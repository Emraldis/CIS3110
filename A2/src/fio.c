#include "fio.h"

void * processParse(char * input){
	
}

void * threadParse(char * input){
	
}

void * burstParse(char * input){
	
}

Process * createProcess(char * input, FILE * inputFile){
    Process * newProcess;
    char * tempString;
	int i;
	Thread * tempThread;

    newProcess = malloc(sizeof(Process));

    tempString = strtok(input, " ");
    newProcess->processNum = atoi(tempString);
    tempString = strtok(NULL, " ");
    newProcess->numThreads = atoi(tempString);

    printf("\nProcess Number: %d\nNumber of Threads: %d\n",newProcess->processNum,newProcess->numThreads);

	if(fgets(input,256,inputFile) != NULL){
		tempThread = createThread(input, inputFile);
	}

	for(i=0;i < (newProcess->numThreads - 1);i++){
	    if(fgets(input,256,inputFile) != NULL){
			
    	}
    }

    return(newProcess);
}

Thread * createThread(char * input, FILE * inputFile){
    Thread * newThread;
    int numBursts;
    int arrivalTime;
    int threadNum;
    char * tempThread;

    tempThread = malloc(sizeof(char)*256);
    newThread = malloc(sizeof(Thread));

	

    return(newThread);
}
