#include <stdio.h>
#include "structures.h"
#include "functions.h"

int main (int argc, char * argv[]) {
	
	Memory * memory;
	Disk * disk;
	char * input;
	Process * currentProcess;
	FILE * inputFile;
	char * fileName;
	int allocationMode;
	Process * tempProcess;
	int tick;
	int loc;
	int locStore;
	int i;
	Stat * statInfo;

	statInfo = malloc(sizeof(Stat));
	tempProcess = malloc(sizeof(Process));
	
	fileName = argv[1];
	
	for(allocationMode=0;allocationMode<4;allocationMode++){	
		memory = malloc(sizeof(memory));
		memory->totalSize = 128;
		disk = malloc(sizeof(disk));
		input = malloc(sizeof(char) * 256);
		memory->memoryArr = malloc(sizeof(Process *) * memory->totalSize);
		disk->prcList = malloc(sizeof(Process));
				
		inputFile = fopen(fileName, "r");
		
		disk->prcList = NULL;
		
		while(fgets(input,256,inputFile) != NULL){
			tempProcess = lineParse(input);
			disk = addToBack(disk,copyProcess(tempProcess));
		}
		fclose(inputFile);
		
		currentProcess = disk->prcList;
		printf("\nProcesses:\n");
		while(currentProcess != NULL){
			printf("\n\tName: %s\n\tSize: %d\n",currentProcess->label,currentProcess->memoryReq);
			currentProcess = currentProcess->next;
		}
		
		tick = 1;
		
		currentProcess = disk->prcList;
		
		switch(allocationMode){
			case 0:
			printf("\nFirst Fit:\n");
			while((disk->prcList != NULL) && (tick <200)){
				//printf("\n@tick: %d",tick);
				//printf("\nThe next process requires %d Megabytes of space.",currentProcess->memoryReq);
				loc = firstFit(memory,currentProcess->memoryReq);
				if(loc >= 0){
					//printf("\nProcess %s fits @ %d!",currentProcess->label,loc);
					if(currentProcess != NULL){
						memory = insert(currentProcess,memory,loc,tick);
						statInfo->loads = tick;
						statInfo = collectStats(memory,statInfo);
						printf("\nPID %s Loaded, Number of Processes: %d, Number of Holes: %d, Percent of Memory Used: %-.1f, Average Amount of Memory Used: %-.1f",currentProcess->label,statInfo->numProcesses,statInfo->numHoles,statInfo->percentMem,statInfo->avgMem);
						disk = removeFromFront(disk);
						currentProcess = disk->prcList;
					}
				}else{
					while(!(loc >= 0)){
						//printf("\nProcess %s doesn't fit.",currentProcess->label);
						memory = removeProcess(memory,disk,0);
						loc = firstFit(memory,currentProcess->memoryReq);
						if(loc >= 0){
							//printf("\nProcess %s fits @ %d!",currentProcess->label,loc);
							if(currentProcess != NULL){
								memory = insert(currentProcess,memory,loc,tick);
								statInfo->loads = tick;
								statInfo = collectStats(memory,statInfo);
								printf("\nPID %s Loaded, Number of Processes: %d, Number of Holes: %d, Percent of Memory Used: %-.1f, Average Amount of Memory Used: %-.1f",currentProcess->label,statInfo->numProcesses,statInfo->numHoles,statInfo->percentMem,statInfo->avgMem);
								disk = removeFromFront(disk);
								currentProcess = disk->prcList;
							}
						}
					}
				}
				tick++;
			}
			printf("\nTotal Loads: %d, Average Number of Processes: %-.1f, Average Number of Holes: %-.1f, Average Memory Usage: %-.1f",statInfo->loads,statInfo->avgProcesses,statInfo->avgHoles,statInfo->avgMem);
			statInfo = clearStats(statInfo);
				break;
			case 1:
			printf("\nNext Fit:\n");
			locStore = 0;
			while((disk->prcList != NULL) && (tick <200)){
				//printf("\n@tick: %d",tick);
				//printf("\nThe next process requires %d Megabytes of space.",currentProcess->memoryReq);
				loc = nextFit(memory,currentProcess->memoryReq,locStore);
				if(loc >= 0){
					locStore = loc;
					//printf("\nProcess %s fits @ %d!",currentProcess->label,loc);
					if(currentProcess != NULL){
						memory = insert(currentProcess,memory,loc,tick);
						statInfo->loads = tick;
						statInfo = collectStats(memory,statInfo);
						printf("\nPID %s Loaded, Number of Processes: %d, Number of Holes: %d, Percent of Memory Used: %-.1f, Average Amount of Memory Used: %-.1f",currentProcess->label,statInfo->numProcesses,statInfo->numHoles,statInfo->percentMem,statInfo->avgMem);
						disk = removeFromFront(disk);
						currentProcess = disk->prcList;
					}
				}else{
					while(!(loc >= 0)){
						locStore = loc;
						//printf("\nProcess %s doesn't fit.",currentProcess->label);
						memory = removeProcess(memory,disk,0);
						loc = nextFit(memory,currentProcess->memoryReq,locStore);
						if(loc >= 0){
							//printf("\nProcess %s fits @ %d!",currentProcess->label,loc);
							if(currentProcess != NULL){
								memory = insert(currentProcess,memory,loc,tick);
								statInfo->loads = tick;
								statInfo = collectStats(memory,statInfo);
								printf("\nPID %s Loaded, Number of Processes: %d, Number of Holes: %d, Percent of Memory Used: %-.1f, Average Amount of Memory Used: %-.1f",currentProcess->label,statInfo->numProcesses,statInfo->numHoles,statInfo->percentMem,statInfo->avgMem);
								disk = removeFromFront(disk);
								currentProcess = disk->prcList;
							}
						}
					}
				}
				tick++;
			}
			printf("\nTotal Loads: %d, Average Number of Processes: %-.1f, Average Number of Holes: %-.1f, Average Memory Usage: %-.1f",statInfo->loads,statInfo->avgProcesses,statInfo->avgHoles,statInfo->avgMem);
			statInfo = clearStats(statInfo);
				break;
			case 2:
			printf("\nBest Fit:\n");
			while((disk->prcList != NULL) && (tick <200)){
				//printf("\n@tick: %d",tick);
				//printf("\nThe next process requires %d Megabytes of space.",currentProcess->memoryReq);
				//getchar();
				loc = bestFit(memory,currentProcess->memoryReq);
				if(loc >= 0){
					//printf("\nProcess %s fits @ %d!",currentProcess->label,loc);
					if(currentProcess != NULL){
						memory = insert(currentProcess,memory,loc,tick);
						statInfo->loads = tick;
						statInfo = collectStats(memory,statInfo);
						printf("\nPID %s Loaded, Number of Processes: %d, Number of Holes: %d, Percent of Memory Used: %-.1f, Average Amount of Memory Used: %-.1f",currentProcess->label,statInfo->numProcesses,statInfo->numHoles,statInfo->percentMem,statInfo->avgMem);
						disk = removeFromFront(disk);
						currentProcess = disk->prcList;
					}
				}else{
					while(!(loc >= 0)){
						//printf("\nProcess %s doesn't fit.",currentProcess->label);
						memory = removeProcess(memory,disk,0);
						loc = bestFit(memory,currentProcess->memoryReq);
						if(loc >= 0){
							//printf("\nProcess %s fits @ %d!",currentProcess->label,loc);
							if(currentProcess != NULL){
								memory = insert(currentProcess,memory,loc,tick);
								statInfo->loads = tick;
								statInfo = collectStats(memory,statInfo);
								printf("\nPID %s Loaded, Number of Processes: %d, Number of Holes: %d, Percent of Memory Used: %-.1f, Average Amount of Memory Used: %-.1f",currentProcess->label,statInfo->numProcesses,statInfo->numHoles,statInfo->percentMem,statInfo->avgMem);
								disk = removeFromFront(disk);
								currentProcess = disk->prcList;
							}
						}
					}
				}
				tick++;
			}
			printf("\nTotal Loads: %d, Average Number of Processes: %-.1f, Average Number of Holes: %-.1f, Average Memory Usage: %-.1f",statInfo->loads,statInfo->avgProcesses,statInfo->avgHoles,statInfo->avgMem);
			statInfo = clearStats(statInfo);
				break;
			case 3:
			printf("\nWorst Fit:\n");
			while((disk->prcList != NULL) && (tick <200)){
				//printf("\n@tick: %d",tick);
				//printf("\nThe next process requires %d Megabytes of space.",currentProcess->memoryReq);
				//getchar();
				loc = worstFit(memory,currentProcess->memoryReq);
				if(loc >= 0){
					//printf("\nProcess %s fits @ %d!",currentProcess->label,loc);
					if(currentProcess != NULL){
						memory = insert(currentProcess,memory,loc,tick);
						statInfo->loads = tick;
						statInfo = collectStats(memory,statInfo);
						printf("\nPID %s Loaded, Number of Processes: %d, Number of Holes: %d, Percent of Memory Used: %-.1f, Average Amount of Memory Used: %-.1f",currentProcess->label,statInfo->numProcesses,statInfo->numHoles,statInfo->percentMem,statInfo->avgMem);
						disk = removeFromFront(disk);
						currentProcess = disk->prcList;
					}
				}else{
					while(!(loc >= 0)){
						//printf("\nProcess %s doesn't fit.",currentProcess->label);
						memory = removeProcess(memory,disk,0);
						loc = worstFit(memory,currentProcess->memoryReq);
						if(loc >= 0){
							//printf("\nProcess %s fits @ %d!",currentProcess->label,loc);
							if(currentProcess != NULL){
								memory = insert(currentProcess,memory,loc,tick);
								statInfo->loads = tick;
								statInfo = collectStats(memory,statInfo);
								printf("\nPID %s Loaded, Number of Processes: %d, Number of Holes: %d, Percent of Memory Used: %-.1f, Average Amount of Memory Used: %-.1f",currentProcess->label,statInfo->numProcesses,statInfo->numHoles,statInfo->percentMem,statInfo->avgMem);
								disk = removeFromFront(disk);
								currentProcess = disk->prcList;
							}
						}
					}
				}
				tick++;
			}
			printf("\nTotal Loads: %d, Average Number of Processes: %-.1f, Average Number of Holes: %-.1f, Average Memory Usage: %-.1f",statInfo->loads,statInfo->avgProcesses,statInfo->avgHoles,statInfo->avgMem);
			statInfo = clearStats(statInfo);
				break;
		}
		
		printf("\n______________________________________________________________________________________________________________\n");
		for(i=0;i < memory->totalSize; i++){
			memory->memoryArr[i] = NULL;	
		}
		while(disk->prcList != NULL){
			disk = removeFromFront(disk);
		}
		
	}
	return(0);
}
