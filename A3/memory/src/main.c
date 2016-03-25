#include <stdio.h>
#include "structures.h"
#include "functions.h"

int main (void) {
	
	Memory * memory;
	Disk * disk;
	char * input;
	Process * currentProcess;
	
	memory = malloc(sizeof(memory));
	disk = malloc(sizeof(disk));
	input = malloc(sizeof(char) * 256);
	
	memory->memoryArr = malloc(sizeof(Process) * 128);
	
	while(gets(input) != NULL){
		disk = addToBack(disk,lineParse(input));
	}
	currentProcess = disk->prcList;
	while(currentProcess != NULL){
		printf("\nName: %s\nSize: %d\n",currentProcess->label,currentProcess->memoryReq);
		currentProcess = currentProcess->next;
	}
	
	return(0);
}
