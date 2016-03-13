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
	int overhead = 0;
	int event =0;
    FILE * inputFile;
    Thread * readyQ;
    Process * currentProcess;
    Process * ProcessList;
	Thread * currentThread;
	Burst * currentBurst;
	Thread * CPU;
	Thread * waitingQ;
	Burst * tempBurst;
	Thread * tempThread;

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
	
	if(debug == 1){
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
	}
	currentProcess = ProcessList;

	
	/***************************************************************************************************************************************
	Running FCFS Simulation:
	***************************************************************************************************************************************/
	tick = 0;
	if(debug == 3){
		printf("\nCreating ReadyQ:\n\n");
	}
	currentProcess = ProcessList;
	for(i=0;i<processNum;i++){
		if(currentProcess->nextThread->arrivalTime == 0){
			printf("\nComparing values:  processNum:  %d  Burst ProcessNum:  %d\n",currentProcess->processNum,currentProcess->nextThread->nextBurst->processNum);
			readyQ = addItem(readyQ,currentProcess->nextThread);
		}
		if(debug == 3){
			printf("\nReadyQ first member: %d\n",readyQ->processNum);
		}
		currentProcess = currentProcess->nextProcess;
	}
	if(debug == 3){
		printf("\nFinished ReadyQ\n\n");
	}
	currentProcess = ProcessList;
	printf("\n TESTS:");
	
	if(debug == 3){
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
	}
	currentProcess = ProcessList;

	printf("\n FINISHED TESTS");
	tick++;
	while((complete == 0) && (tick <400)){
		
		
		
		if((CPU == NULL) && (readyQ != NULL) && (overhead == 0)){
			CPU = copyThread(readyQ);
			CPU->nextThread = NULL;
			readyQ = removeFirstThread(readyQ);
			CPU->nextBurst->entryTime = tick;
			printf("\nreadyQ->CPU");
			event = 1;
		}
		if(CPU != NULL){
			CPU->nextBurst->remainingTime--;
			if(CPU->nextBurst->remainingTime == 0){
				CPU->waitTime = CPU->nextBurst->IOTime;
				//printf("\nWait time set to: %d from the burst IO time of: %d", CPU->waitTime, CPU->nextBurst->IOTime);
				CPU->nextBurst = removeFirstBurst(CPU->nextBurst);
				if(readyQ != NULL){
					if(CPU->processNum == readyQ->processNum){
						overhead = threadTrans;
						printf("\nThe next thread is from the same process");
					}else{
						overhead = processTrans;
						printf("\nThe next thread is from a different process");
					}
				}
				if(CPU->nextBurst != NULL){
					printf("\nCPU->waitingQ");
					waitingQ = addItem(waitingQ,CPU);
					printf("\nTesting waitingQ wait time: %d",waitingQ->waitTime);
				}
				CPU = removeFirstThread(CPU);
				event = 1;
			}
		}
		printf("\ntick: %d",tick);
		if(tick % 5 == 0){
			//getchar();
		}
		if(waitingQ != NULL){
			currentThread = waitingQ;
			while(currentThread != NULL){
				if(currentThread->nextThread != NULL){
					if((currentThread->nextThread->waitTime == 0) && (currentThread != waitingQ)){
						printf("\nwaitingQ->readyQ");
						readyQ = addItem(readyQ,currentThread->nextThread);
						tempThread = currentThread->nextThread;
						currentThread->nextThread = tempThread->nextThread;
						event = 1;
					}
				}else{
					if((currentThread->waitTime == 0) && (currentThread != NULL) && (currentThread == waitingQ)){
						readyQ = addItem(readyQ,currentThread);
						waitingQ = removeFirstThread(waitingQ);
						event = 1;
					}
				}
				if(currentThread != NULL){
					currentThread->waitTime--;
					currentThread = currentThread->nextThread;
				}
			}
		}
		if((debug == 3) && (tick % 10 == 0)){
			//getchar();
			if(CPU != NULL){
				printf("\n\tBurst in CPU:\n\tProcess: %d\tThread: %d\tBurst: %d\n",CPU->processNum,CPU->threadNum,CPU->nextBurst->burstNum);
				printf("\tCurrent remaining CPU time: %d\n",CPU->nextBurst->remainingTime);
			}
		}
		
	/***************************************************************************************************************************************
	Printing all Q's:
	***************************************************************************************************************************************/
				
		if((debug == 3) && (event != 0)){
			printf("\n\nDEBUGGING all Q's @ tick = %d\n",tick);
			printf("\nREADY QUEUE:\n");
			if(readyQ != NULL){
				currentThread = readyQ;
				while(currentThread->nextThread != NULL){
					printf("\n\tProcess: %d\tThread: %d\tBurst: %d\n",currentThread->processNum,currentThread->threadNum,currentThread->nextBurst->burstNum);
					currentThread = currentThread->nextThread;
				}
				if(currentThread->nextThread == NULL){
					printf("\n\tProcess: %d\tThread: %d\tBurst: %d\n",currentThread->processNum,currentThread->threadNum,currentThread->nextBurst->burstNum);
				}
			}else{
				printf("\n\tEMPTY READY QUEUE\n");
			}
			printf("\nCPU:\n");
			if(CPU != NULL){
				printf("\n\tProcess: %d\tThread: %d\tBurst: %d\n\tTime Remaining: %d\n",CPU->processNum,CPU->threadNum,CPU->nextBurst->burstNum,CPU->nextBurst->remainingTime);
			}else{
				printf("\n\tEMPTY CPU\n");
				if(overhead != 0){
					printf("\n\tOverhead time remaining: %d", overhead);
				}
			}
			printf("\nWAITING QUEUE:\n");
			if(waitingQ != NULL){
				currentThread = waitingQ;
				while(currentThread->nextThread != NULL){
					printf("\n\tProcess: %d\tThread: %d\tBurst: %d\n\tRemaining wait time: %d\n",currentThread->processNum,currentThread->threadNum,currentThread->nextBurst->burstNum,currentThread->waitTime);
					currentThread = currentThread->nextThread;
				}
				if(currentThread->nextThread == NULL){
					printf("\n\tProcess: %d\tThread: %d\tBurst: %d\n\tRemaining wait time: %d\n",currentThread->processNum,currentThread->threadNum,currentThread->nextBurst->burstNum,currentThread->waitTime);
				}
			}else{
				printf("\n\tEMPTY WAIT QUEUE\n");
			}
		}
		if(overhead != 0){
			overhead--;
		}
		if((CPU == NULL) && (readyQ == NULL) && (waitingQ == NULL)){
			complete = 1;
		}
		event = 0;
		tick++;
	}
	printf("\nSimulation ended after %d Ticks\n",tick);

    return(0);
}
