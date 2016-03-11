#include <stdio.h>
#include <string.h>
#include "fio.h"
#include "linkedList.h"
#include "process.h"

int main (int argc, char * argv[]){

    char * fileName;
    int processTrans;
    int threadTrans;
    char * input;
    int processNum;
    int threadNum;
    char * tempString;
    int i;
    int j;
    int k;
    FILE * inputFile;
    Process * readyQ;
    Process * currentProcess;
    Process * ProcessList;
	Thread * currentThread;
	Burst * currentBurst;

    input = malloc(sizeof(char)*256);

    fileName = argv[1];
    printf("\nDataFile: %s",fileName);
    inputFile = fopen(fileName,"r");
	if(fgets(input,256,inputFile) != NULL){
        tempString = strtok(input, " ");
        if(tempString != NULL){
            processNum = atoi(tempString);
        }
        tempString = strtok(NULL, " ");
        if (tempString != NULL){
            processTrans = atoi(tempString);
        }
        tempString = strtok(NULL, " ");
        if (tempString != NULL){
            threadTrans = atoi(tempString);
        }
        printf("\nNumber of Processes: %d\n Overhead between Threads of the same Process: %d\nOverhead between Threads of different Processes: %d\n",processNum,processTrans,threadTrans);
		if(fgets(input,256,inputFile)){
			ProcessList = createProcess(input,inputFile);
			currentProcess = ProcessList;
		}
        for(i=0;i<(processNum - 1);i++){
        	printf("\n");
            if(fgets(input,256,inputFile) != NULL){
                currentProcess->nextProcess = createProcess(input,inputFile);
				currentProcess = currentProcess->nextProcess;
            }
        }
    }
	currentProcess->nextProcess = NULL;
	currentProcess = ProcessList;
	while(currentProcess->nextProcess != NULL){
		printf("\nProcess Number: %d\nNumber of Threads: %d",currentProcess->processNum,currentProcess->numThreads);
		currentThread = currentProcess->nextThread;
		k = 1;
		while(k != 0){
			printf("\n\tThread Number: %d\n\t Arrival Time: %d \n\tNumber of Bursts: %d\n",currentThread->threadNum,currentThread->arrivalTime,currentThread->numBursts);
			if(currentThread->nextThread != NULL){
				printf("\n\tNext Thread Number: %d\n",currentThread->nextThread->threadNum);
			}
			currentBurst = currentThread->nextBurst;
			j = 1;
			while(j != 0){
				printf("\n\t\tBurst Number: %d\n\t\tCPU Time: %d\n\t\tIO Time: %d\n",currentBurst->burstNum, currentBurst->CPUTime, currentBurst->IOTime);
				if(currentBurst->nextBurst != NULL){
					currentBurst = currentBurst->nextBurst;
				}else{
					j = 0;
				}
				getchar();
			}
			if(currentThread->nextThread != NULL){
				currentThread = currentThread->nextThread;
			}else{
				k =0;
			}
		}
	}

    return(0);
}
