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
	int verbose = 1;
	int rr = 0;
	int rrq = 50;
	int quantumTick;
	int numThreads = 0;
	int avTurnTime = 0;
	int accumulatedOverhead = 0;
	float CPUUsage;
    //FILE * inputFile;
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
	
    //fileName = argv[1];
    //inputFile = fopen(fileName,"r");
	if(gets(input) != NULL){
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
		if(gets(input)){
			ProcessList = createProcess(input);
			currentProcess = ProcessList;
		}
        for(i=0;i<(processNum - 1);i++){
        	printf("\n");
            if(gets(input) != NULL){
                currentProcess->nextProcess = createProcess(input);
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
				printf("\n\tThread Number: %d\n\tArrival Time: %d \n\tNumber of Bursts: %d\n",currentThread->threadNum,currentThread->arrivalTime,currentThread->numBursts);
				currentBurst = currentThread->nextBurst;
				j = 1;
				while(j != 0){
					printf("\n\t\tBurst Number: %d\n\t\tCPU Time: %d\n\t\tIO Time: %d\n",currentBurst->burstNum, currentBurst->CPUTime, currentBurst->IOTime);
					if(currentBurst->nextBurst != NULL){
						currentBurst = currentBurst->nextBurst;
					}else{
						j = 0;
					}
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
	quantumTick = rrq;
	if(debug == 3){
		printf("\nCreating ReadyQ:\n\n");
	}
	currentProcess = ProcessList;
	for(i=0;i<processNum;i++){
		currentThread = currentProcess->nextThread;
		for(j=0;j < currentProcess->numThreads; j++){		
			if(debug == 3){
				printf("\nCurrent Thread: P: %d T: %d\n",currentThread->processNum,currentThread->threadNum);
			}
			if(currentThread->arrivalTime == 0){
				if(debug == 3){
					printf("\nAdding Item to readyQ:\n\tProcess Num: %d\tThread Num: %d\n",currentThread->processNum,currentThread->threadNum);
				}
				if(verbose == 1){
					printf("\nAt Time %d Thread %d of Process %d moves from New to Ready",tick,currentThread->threadNum,currentThread->processNum);
				}
				readyQ = addItem(readyQ,currentThread);
			}else{
				if(debug == 3){
					printf("\nAdding Item to waitingQ:\n\tProcess Num: %d\tThread Num: %d\n",currentThread->processNum,currentThread->threadNum);
				}
				currentThread->waitTime = currentThread->arrivalTime;
				waitingQ = addItem(waitingQ,currentThread);
			}
			currentThread = currentThread->nextThread;
		}
		currentProcess = currentProcess->nextProcess;
	}
	if(debug == 3){
		printf("\nFinished ReadyQ\n\n");
	}
	currentProcess = ProcessList;
	/*
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

	printf("\n FINISHED TESTS\n");
	*/
	
	if(debug == 3){
		printf("\nBeginning simulation\n***********************************************************************************************************************************\n");
	}
	while((complete == 0) && (tick <900)){
		if(waitingQ != NULL){
			currentThread = waitingQ;
			while(currentThread != NULL){
				if(currentThread->nextThread != NULL){
					if(/*(*/currentThread->nextThread->waitTime == 0/*) && (currentThread != waitingQ)*/){
						if(verbose == 1){
							if(currentThread->nextBurst->burstNum == 1){
								printf("\nAt Time %d Thread %d of Process %d moves from New to Ready",tick,currentThread->threadNum,currentThread->processNum);
							}else{
								printf("\nAt Time %d Thread %d of Process %d moves from Blocked to Ready",tick,currentThread->threadNum,currentThread->processNum);
							}
						}
						readyQ = addItem(readyQ,currentThread->nextThread);
						tempThread = currentThread->nextThread;
						currentThread->nextThread = tempThread->nextThread;
						event = 1;
					}
					if(currentThread == waitingQ){
						if(currentThread->waitTime == 0){
							if(verbose == 1){
								if(currentThread->nextBurst->burstNum == 1){
									printf("\nAt Time %d Thread %d of Process %d moves from New to Ready",tick,currentThread->threadNum,currentThread->processNum);
								}else{
									printf("\nAt Time %d Thread %d of Process %d moves from Blocked to Ready",tick,currentThread->threadNum,currentThread->processNum);
								}
							}
							readyQ = addItem(readyQ,currentThread);
							waitingQ = removeFirstThread(waitingQ);
							event = 1;
						}
					}
				}else{
					if(currentThread == waitingQ){
						if(currentThread->waitTime == 0){
							if(verbose == 1){
								if(currentThread->nextBurst->burstNum == 1){
									printf("\nAt Time %d Thread %d of Process %d moves from New to Ready",tick,currentThread->threadNum,currentThread->processNum);
								}else{
									printf("\nAt Time %d Thread %d of Process %d moves from Blocked to Ready",tick,currentThread->threadNum,currentThread->processNum);
								}
							}
							readyQ = addItem(readyQ,currentThread);
							waitingQ = removeFirstThread(waitingQ);
							event = 1;
						}
					}
				}
				if(currentThread != NULL){
					currentThread->waitTime--;
					currentThread = currentThread->nextThread;
				}
			}
		}
		if((CPU == NULL) && (readyQ != NULL) && (overhead == 0)){
			CPU = copyThread(readyQ);
			CPU->nextThread = NULL;
			readyQ = removeFirstThread(readyQ);
			CPU->nextBurst->entryTime = tick;
			if(verbose == 1){
						printf("\nAt Time %d Thread %d of Process %d moves from Ready to Running",tick,CPU->threadNum,CPU->processNum);
			}
			if(rr == 1){
				quantumTick = rrq;
			}
			event = 1;
		}
		if(CPU != NULL){
			CPU->nextBurst->remainingTime--;
			if(CPU->nextBurst->remainingTime < 0){
				CPU->waitTime = CPU->nextBurst->IOTime;
				CPU->nextBurst = removeFirstBurst(CPU->nextBurst);
				if(readyQ != NULL){
					if(CPU->processNum == readyQ->processNum){
						overhead = processTrans;
					}else{
						overhead = threadTrans;
					}
				}
				if(CPU->nextBurst != NULL){
					if(verbose == 1){
						printf("\nAt Time %d Thread %d of Process %d moves from Running to Blocked",tick,CPU->threadNum,CPU->processNum);
					}
					waitingQ = addItem(waitingQ,CPU);
				}else{
					if(verbose == 1){
						printf("\nAt Time %d Thread %d of Process %d moves from Running to Terminated",tick,CPU->threadNum,CPU->processNum);
					}
					CPU->turnaroundTime = (tick - CPU->arrivalTime);
					avTurnTime = avTurnTime + CPU->turnaroundTime;
					numThreads++;
					if(rr == 1){
						quantumTick = rrq;
					}
				}
				CPU = removeFirstThread(CPU);
				event = 1;
			}else{
				if(rr == 1){
					if(quantumTick == 0){
						if(readyQ != NULL){
							if(CPU->processNum == readyQ->processNum){
								overhead = processTrans;
							}else{
								overhead = threadTrans;
							}
						}
						CPU->nextBurst->remainingTime++;
						readyQ = addItem(readyQ,CPU);
						if(verbose == 1){
							printf("\nAt Time %d Thread %d of Process %d moves from Running to Ready",tick,CPU->threadNum,CPU->processNum);
						}
						CPU = removeFirstThread(CPU);
						quantumTick = rrq; 
						event = 1;
					}
				}
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
			printf("\ntick: %d",tick);
			if(tick % 5 == 0){
			}
		}
		accumulatedOverhead = (accumulatedOverhead + overhead);
		if(overhead != 0){
			overhead--;
		}
		if((CPU == NULL) && (readyQ == NULL) && (waitingQ == NULL)){
			complete = 1;
		}
		if((verbose == 1) && (event == 1) && (debug == 0)){
			printf("\n");
		}
		event = 0;
		if(rr == 1){
			quantumTick--;
		}
		tick++;
	}
	tick--;
	if(verbose == 1){
		printf("\nSimulation ended after %d Ticks\n",tick);
	}
	avTurnTime = (avTurnTime/numThreads);
	CPUUsage = ((1-(accumulatedOverhead/tick)) * 100);
	printf("\nSimulation results:");
	printf("\nTotal Time required: %d",tick);
	printf("\nAverage turnaround time: %d",avTurnTime);
	printf("\nCPU utilization: %f \%\n",CPUUsage);

    return(0);
}
