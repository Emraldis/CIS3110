#include <stdio.h>
#include <string.h>
#include "fio.h"
#include "linkedList.h"

int main (int argc, char * argv[]){

    int processTrans;
    int threadTrans;
    char * input;
    int processNum;
    char * tempString;
    int i;
    int j;
    int k;
	float tick;
	int debug = 0;
	int complete = 0;
	int overhead = 0;
	int event =0;
	int verbose = 0;
	int detailed = 0;
	int rr = 0;
	int rrq = 1;
	int quantumTick;
	int numThreads = 0;
	int avTurnTime = 0;
	float accumulatedOverhead = 0;
	float CPUUsage;
    Thread * readyQ;
    Process * currentProcess;
    Process * ProcessList;
	Thread * currentThread;
	Burst * currentBurst;
	Thread * CPU;
	Thread * waitingQ;
	Thread * tempThread;
	Thread * finished;

    input = malloc(sizeof(char)*256);
	readyQ = NULL;
	CPU = NULL;
	waitingQ = NULL;
	finished = NULL;

	/***************************************************************************************************************************************
	Creating the Lists:
	***************************************************************************************************************************************/
	
	for(i=0;i<argc;i++){
		if(strcmp("-d",argv[i]) == 0){
			detailed = 1;
		}else if(strcmp("-r",argv[i]) == 0){
			rr = 1;
		}else if(strcmp("-v",argv[i]) == 0){
			verbose = 1;
		}
		if((rr == 1) && (atoi(argv[i]) != 0)){
			rrq = atoi(argv[i]);
		}
	}
	
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
					printf("\nAt Time %-.0f Thread %d of Process %d moves from New to Ready",tick,currentThread->threadNum,currentThread->processNum);
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
	
	if(debug == 3){
		printf("\nBeginning simulation\n***********************************************************************************************************************************\n");
	}
	while((complete == 0) && (tick <900)){
		if((CPU == NULL) && (readyQ != NULL) && (overhead == 0)){
			CPU = copyThread(readyQ);
			CPU->nextThread = NULL;
			readyQ = removeFirstThread(readyQ);
			CPU->nextBurst->entryTime = tick;
			if(verbose == 1){
						printf("\nAt Time %-.0f Thread %d of Process %d moves from Ready to Running",tick,CPU->threadNum,CPU->processNum);
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
						accumulatedOverhead = (accumulatedOverhead + overhead);
					}else{
						overhead = threadTrans;
						accumulatedOverhead = (accumulatedOverhead + overhead);
					}
				}
				if(CPU->nextBurst != NULL){
					if(verbose == 1){
						printf("\nAt Time %-.0f Thread %d of Process %d moves from Running to Blocked",tick,CPU->threadNum,CPU->processNum);
					}
					waitingQ = addItem(waitingQ,CPU);
				}else{
					if(verbose == 1){
						printf("\nAt Time %-.0f Thread %d of Process %d moves from Running to Terminated",tick,CPU->threadNum,CPU->processNum);
					}
					CPU->turnaroundTime = (tick - CPU->arrivalTime);
					avTurnTime = avTurnTime + CPU->turnaroundTime;
					numThreads++;
					CPU->finishTime = tick;
					finished = addItem(finished,CPU);
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
								accumulatedOverhead = (accumulatedOverhead + overhead);
							}else{
								overhead = threadTrans;
								accumulatedOverhead = (accumulatedOverhead + overhead);
							}
						}
						CPU->nextBurst->remainingTime++;
						readyQ = addItem(readyQ,CPU);
						if(verbose == 1){
							printf("\nAt Time %-.0f Thread %d of Process %d moves from Running to Ready",tick,CPU->threadNum,CPU->processNum);
						}
						CPU = removeFirstThread(CPU);
						quantumTick = rrq; 
						event = 1;
					}
				}
			}
		}
		if(waitingQ != NULL){
			currentThread = waitingQ;
			while(currentThread != NULL){
				if(currentThread->nextThread != NULL){
					if(currentThread->nextThread->waitTime == 0){
						if(verbose == 1){
							if(currentThread->nextBurst->burstNum == 1){
								printf("\nAt Time %-.0f Thread %d of Process %d moves from New to Ready",tick,currentThread->threadNum,currentThread->processNum);
							}else{
								printf("\nAt Time %-.0f Thread %d of Process %d moves from Blocked to Ready",tick,currentThread->threadNum,currentThread->processNum);
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
									printf("\nAt Time %-.0f Thread %d of Process %d moves from New to Ready",tick,currentThread->threadNum,currentThread->processNum);
								}else{
									printf("\nAt Time %-.0f Thread %d of Process %d moves from Blocked to Ready",tick,currentThread->threadNum,currentThread->processNum);
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
									printf("\nAt Time %-.0f Thread %d of Process %d moves from New to Ready",tick,currentThread->threadNum,currentThread->processNum);
								}else{
									printf("\nAt Time %-.0f Thread %d of Process %d moves from Blocked to Ready",tick,currentThread->threadNum,currentThread->processNum);
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
		
	/***************************************************************************************************************************************
	Printing all Q's:
	***************************************************************************************************************************************/
				
		if((debug == 3) && (event != 0)){
			printf("\n\nDEBUGGING all Q's @ tick = %-.0f\n",tick);
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
			printf("\ntick: %-.0f",tick);
		}
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
		tick = (tick + 1);
	}
	tick = (tick - 1);
	if(verbose == 1){
		printf("\nSimulation ended after %-.0f Ticks\n",tick);
	}
	avTurnTime = (avTurnTime/numThreads);
	printf("\nAccumulated Ovehead: %-.0f",accumulatedOverhead);
	CPUUsage = ((1-(accumulatedOverhead/tick)) * 100);
	if(rr == 0){
		printf("\nFCFS Scheduling");
	}else{
		printf("\nRound Robin Scheduling with Time Quantum %d",rrq);
	}
	printf(" Simulation results:");
	printf("\nTotal Time required: %-.0f",tick);
	printf("\nAverage turnaround time: %d",avTurnTime);
	printf("\nCPU utilization: %f\n",CPUUsage);
	
	if(detailed == 1){
		getchar();
		currentThread = finished;
		while(currentThread != NULL){
			printf("\nThread %d of Process %d:\narrival time: %d\nservice time: %d I/O time: %d turnaround time: %d finish time: %d\n",currentThread->threadNum,currentThread->processNum,currentThread->arrivalTime,currentThread->serviceTime,currentThread->IOTime,currentThread->turnaroundTime,currentThread->finishTime);
			currentThread = currentThread->nextThread;
			}
	}

    return(0);
}
