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
	int tick;
	int debug = 0;
	int complete = 0;
    FILE * inputFile;
    Burst * readyQ;
    Process * currentProcess;
    Process * ProcessList;
	Thread * currentThread;
	Burst * currentBurst;

    input = malloc(sizeof(char)*256);
	//readyQ = malloc(sizeof(Burst));
	readyQ = NULL;

	/***************************************************************************************************************************************
	Creating the Lists:
	***************************************************************************************************************************************/
	
    fileName = argv[1];
	if (argv[2] != NULL){
		debug = atoi(argv[2]);
	}
	if (debug == 2){
		printf("\nDataFile: %s",fileName);
	}
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
	
	
	/***************************************************************************************************************************************
	List Debug Code:
	***************************************************************************************************************************************/
	
	//if(debug == 1){
        printf("\nNumber of Processes: %d\n Overhead between Threads of the same Process: %d\nOverhead between Threads of different Processes: %d\n",processNum,processTrans,threadTrans);
		i = 1;
		while(i != 0){
			printf("\nProcess Number: %d\nNumber of Threads: %d\n",currentProcess->processNum,currentProcess->numThreads);
			currentThread = currentProcess->nextThread;
			k = 1;
			while(k != 0){
				printf("\n\tThread Number: %d\n\t Arrival Time: %d \n\tNumber of Bursts: %d\n",currentThread->threadNum,currentThread->arrivalTime,currentThread->numBursts);
				currentBurst = currentThread->nextBurst;
				j = 1;
				while(j != 0){
					printf("\n\t\tBurst Number: %d\n\t\tCPU Time: %d\n\t\tIO Time: %d\n",currentBurst->burstNum, currentBurst->CPUTime, currentBurst->IOTime);
					if(currentBurst->nextBurst != NULL){
						currentBurst = currentBurst->nextBurst;
					}else{
						j = 0;
					}
					//getchar();
				}
				if(currentThread->nextThread != NULL){
					currentThread = currentThread->nextThread;
				}else{
					k = 0;
				}
			}
			if(currentProcess->nextProcess != NULL){
				currentProcess = currentProcess->nextProcess;
			}else{
				i = 0;
			}
		}
	//}

	
	/***************************************************************************************************************************************
	Running FCFS Simulation:
	***************************************************************************************************************************************/
	tick = 0;
	if(debug == 3){
		printf("\nGot here\n");
	}
	for(i=0;i<processNum;i++){
		if(currentProcess->nextThread->arrivalTime == 0){
			if(debug == 3){
				printf("\nIn a loop\n");
			}
			readyQ = addItem(readyQ,currentProcess->nextThread->nextBurst);
		}
		if(debug == 3){
			printf("\nend of a loop\n");
			printf("\nReadyQ first member: %d\n",readyQ->burstNum);
		}
	}
	if(debug == 3){
		printf("\nGot here\n");
	}
	
	if(debug == 3){
		printf("\nDEBUGGING ReadyQ\n");
		currentBurst = readyQ;
		while(currentBurst->nextBurst != NULL){
			printf("\n\tProcess: %d\tThread: %d\tBurst: %d\n",currentBurst->processNum,currentBurst->threadNum,currentBurst->burstNum);
		}
	}
	/*while(complete == 0){
		
		
		
		tick++;
	}*/
	
    return(0);
}
