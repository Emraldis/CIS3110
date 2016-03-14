#include "fio.h"

Process * createProcess(char * input){
    Process * newProcess;
    char * tempString;
	int i;
	Thread * tempThread;
	

    newProcess = malloc(sizeof(Process));

    tempString = strtok(input, " ");
    newProcess->processNum = atoi(tempString);
    tempString = strtok(NULL, " ");
    newProcess->numThreads = atoi(tempString);

	if(gets(input) != NULL){
		tempThread = createThread(input,newProcess->processNum);
	}
	newProcess->nextThread = tempThread;
	for(i=0;i < (newProcess->numThreads - 1);i++){
	    if(gets(input) != NULL){
			tempThread->nextThread = createThread(input,newProcess->processNum);
			tempThread = tempThread->nextThread;
    	}
    }
	tempThread->nextThread = NULL;
	tempThread = newProcess->nextThread;
	newProcess->complete = 0;
    return(newProcess);
}

Thread * createThread(char * input, int processNum){
    Thread * newThread;
    Burst * tempBurst;
    char * tempString;
    int i;

    newThread = malloc(sizeof(Thread));

	newThread->serviceTime = 0;
	newThread->IOTime = 0;
	tempString = strtok(input, " ");
	newThread->threadNum = atoi(tempString);
	tempString = strtok(NULL, " ");
	newThread->arrivalTime = atoi(tempString);
	tempString = strtok(NULL, " ");
	newThread->numBursts = atoi(tempString);
	newThread->processNum = processNum;
	newThread->waitTime = 0;
	if(gets(input) != NULL){
		tempBurst = createBurst(input,processNum);
		tempBurst->threadNum = newThread->threadNum;
		tempBurst->readyTime = newThread->arrivalTime;
		newThread->serviceTime = (newThread->serviceTime + tempBurst->CPUTime);
		newThread->IOTime = (newThread->IOTime + tempBurst->IOTime);
	}
	newThread->nextBurst = tempBurst;
	for(i = 0;i < (newThread->numBursts - 1);i++){
		if(gets(input)){
			tempBurst->nextBurst = createBurst(input,processNum);
			tempBurst = tempBurst->nextBurst;
			tempBurst->threadNum = newThread->threadNum;
			newThread->serviceTime = (newThread->serviceTime + tempBurst->CPUTime);
			newThread->IOTime = (newThread->IOTime + tempBurst->IOTime);
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
	newBurst->readyTime = -1;
	newBurst->remainingTime = newBurst->CPUTime;
	if(tempString != NULL){
		newBurst->IOTime = atoi(tempString);
	}else{
		newBurst->IOTime = 0;
	}
	newBurst->processNum = processNum;
	return(newBurst);
}
