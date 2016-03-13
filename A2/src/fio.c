#include "fio.h"

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

	if(fgets(input,256,inputFile) != NULL){
		tempThread = createThread(input, inputFile,processNum);
		tempThread->processNum = newProcess->processNum;
	}
	newProcess->nextThread = tempThread;
	for(i=0;i < (newProcess->numThreads - 1);i++){
	    if(fgets(input,256,inputFile) != NULL){
			tempThread->nextThread = createThread(input,inputFile,newProcess->processNum);
			tempThread = tempThread->nextThread;
			tempThread->processNum = newProcess->processNum;
    	}
    }
	tempThread->nextThread = NULL;
	tempThread = newProcess->nextThread;
	newProcess->complete = 0;
    return(newProcess);
}

Thread * createThread(char * input, FILE * inputFile, int processNum){
    Thread * newThread;
    Burst * tempBurst;
    char * tempString;
    int i;

    newThread = malloc(sizeof(Thread));

	tempString = strtok(input, " ");
	newThread->threadNum = atoi(tempString);
	tempString = strtok(NULL, " ");
	newThread->arrivalTime = atoi(tempString);
	tempString = strtok(NULL, " ");
	newThread->numBursts = atoi(tempString);
	if(fgets(input,256,inputFile) != NULL){
		tempBurst = createBurst(input,processNum);
		tempBurst->threadNum = newThread->threadNum;
		tempBurst->readyTime = newThread->arrivalTime;
	}
	newThread->nextBurst = tempBurst;
	for(i = 0;i < (newThread->numBursts - 1);i++){
		if(fgets(input,256,inputFile)){
			tempBurst->nextBurst = createBurst(input,processNum);
			tempBurst = tempBurst->nextBurst;
			tempBurst->threadNum = newThread->threadNum;
		}
	}
	tempBurst->nextBurst = NULL;
	tempBurst = newThread->nextBurst;

    return(newThread);
}

Burst * createBurst(char * input, int processNum){
	Burst * newBurst;
	char * tempString;

	newBurst = malloc(sizeof(Burst));

	tempString = strtok(input," ");
	newBurst->burstNum = atoi(tempString);
	tempString = strtok(NULL," ");
	newBurst->CPUTime = atoi(tempString);
	tempString = strtok(NULL," ");
	if(tempString != NULL){
		newBurst->IOTime = atoi(tempString);
	}else{
		newBurst->IOTime = 0;
	}
	return(newBurst);
}
