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

//    printf("\nProcess Number: %d\nNumber of Threads: %d\n",newProcess->processNum,newProcess->numThreads);

	if(fgets(input,256,inputFile) != NULL){
		tempThread = createThread(input, inputFile);
	}
	newProcess->nextThread = tempThread;
	for(i=0;i < (newProcess->numThreads - 1);i++){
	    if(fgets(input,256,inputFile) != NULL){
			tempThread->nextThread = createThread(input,inputFile);
			tempThread = tempThread->nextThread;
    	}
    }
	tempThread->nextThread = NULL;
	tempThread = newProcess->nextThread;
	/*while(tempThread->nextThread != NULL){
		printf("\n\tThread Number: %d\n\tArrival Time: %d\n\tNumber of CPU Bursts: %d\n",tempThread->threadNum,tempThread->arrivalTime,tempThread->numBursts);
	}*/

    return(newProcess);
}

Thread * createThread(char * input, FILE * inputFile){
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
//	printf("\n\tThread Number: %d\n\tArrival Time: %d\n\tNumber of CPU Bursts: %d\n",newThread->threadNum,newThread->arrivalTime,newThread->numBursts);

	if(fgets(input,256,inputFile) != NULL){
		tempBurst = createBurst(input);
	}
	newThread->nextBurst = tempBurst;
	for(i = 0;i < (newThread->numBursts - 1);i++){
		if(fgets(input,256,inputFile)){
			tempBurst->nextBurst = createBurst(input);
			tempBurst = tempBurst->nextBurst;
		}
	}
	tempBurst->nextBurst = NULL;
	tempBurst = newThread->nextBurst;

    return(newThread);
}

Burst * createBurst(char * input){
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
//	printf("\n\t\tBurst Number: %d\n\t\tCPU Time: %d\n\t\tI/O Time: %d\n",newBurst->burstNum,newBurst->CPUTime,newBurst->IOTime);

	return(newBurst);
}
