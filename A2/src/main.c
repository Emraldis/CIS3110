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
	Burst * CPU;
	Burst * waitingQ;
	Burst * tempBurst;

    input = malloc(sizeof(char)*256);
	readyQ = NULL;
	CPU = NULL;
	waitingQ = NULL;

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
	currentProcess = ProcessList;

	
	/***************************************************************************************************************************************
	Running FCFS Simulation:
	***************************************************************************************************************************************/
	tick = 0;
	if(debug == 3){
		printf("\nCreating ReadyQ:\n\n");
	}
	for(i=0;i<processNum;i++){
		if(currentProcess->nextThread->arrivalTime == 0){
			printf("\nComparing values:  processNum:  %d  Burst ProcessNum:  %d\n",currentProcess->processNum,currentProcess->nextThread->nextBurst->processNum);
			readyQ = addItem(readyQ,currentProcess->nextThread->nextBurst);
		}
		if(debug == 3){
			printf("\nReadyQ first member: %d\n",readyQ->processNum);
		}
		currentProcess = currentProcess->nextProcess;
	}
	if(debug == 3){
		printf("\nFinished ReadyQ\n\n");
	}
	while(tick <= 400){
		if((debug == 3) && (tick % 10 == 0)){
			printf("\nDEBUGGING ReadyQ @ tick = %d\n",tick);
			currentBurst = readyQ;
			while(currentBurst->nextBurst != NULL){
				printf("\n\tProcess: %d\tThread: %d\tBurst: %d\n",currentBurst->processNum,currentBurst->threadNum,currentBurst->burstNum);
				currentBurst = currentBurst->nextBurst;
			}
			if(currentBurst->nextBurst == NULL){
				printf("\n\tProcess: %d\tThread: %d\tBurst: %d\n",currentBurst->processNum,currentBurst->threadNum,currentBurst->burstNum);
			}
		}
		if(CPU == NULL){
			CPU = copyItem(readyQ);
			CPU->nextItem = NULL; 
			printf("\nAdding to CPU");
		}
		if((debug == 3) && (tick % 10 == 0)){
			//getchar();
			if(CPU != NULL){
				printf("\n\tBurst in CPU:\n\tProcess: %d\tThread: %d\tBurst: %d\n",CPU->processNum,CPU->threadNum,CPU->burstNum);
			}
		}
		tick++;
	}
	
	//TEST:
        printf("\nNumber of Processes: %d\n Overhead between Threads of the same Process: %d\nOverhead between Threads of different Processes: %d\n",processNum,processTrans,threadTrans);
		i = 1;
		while(i != 0){
			printf("\ntest1");
			getchar();
			printf("\nProcess Number: %d\nNumber of Threads: %d\n",currentProcess->processNum,currentProcess->numThreads);
			getchar();
			currentThread = currentProcess->nextThread;
			getchar();
			k = 1;
			while(k != 0){
				printf("\ntest2");
				getchar();
				printf("\n\tThread Number: %d\n\t Arrival Time: %d \n\tNumber of Bursts: %d\n",currentThread->threadNum,currentThread->arrivalTime,currentThread->numBursts);
				currentBurst = currentThread->nextBurst;
				j = 1;
				while(j != 0){
					printf("\ntest3");
					getchar();
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
	currentProcess = ProcessList;

    return(0);
}
