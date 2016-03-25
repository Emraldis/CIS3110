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
		while(currentProcess != NULL){
			printf("\nName: %s\nSize: %d\n",currentProcess->label,currentProcess->memoryReq);
			currentProcess = currentProcess->next;
		}
		
		tick = 0;
		currentProcess = disk->prcList;
		
		switch(allocationMode){
			case 0:
			while((disk->prcList != NULL) && (tick <20)){
				printf("\n@tick: %d",tick);
				
				if(fits(memory,currentProcess->memoryReq) >= 0){
					printf("\nProcess %s fits!",currentProcess->label);
					currentProcess = currentProcess->next;
				}else{
					printf("\nProcess %s doesn't fit.",currentProcess->label);					
				}
				
				tick++;
			}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
		}
		
		printf("\n______________________________________________________________________________________________________________\n");
		
		free(memory->memoryArr);
		free(disk->prcList);
		free(input);
		free(disk);
		free(memory);
		
	}
	return(0);
}
