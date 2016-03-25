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
	
	memory = malloc(sizeof(memory));
	disk = malloc(sizeof(disk));
	input = malloc(sizeof(char) * 256);
	memory->memoryArr = malloc(sizeof(Process) * 128);
	
	fileName = argv[1];
	
	inputFile = fopen(fileName, "r");
	
	while(fgets(input,256,inputFile) != NULL){
		disk = addToBack(disk,lineParse(input));
	}
	currentProcess = disk->prcList;
	while(currentProcess != NULL){
		printf("\nName: %s\nSize: %d\n",currentProcess->label,currentProcess->memoryReq);
		currentProcess = currentProcess->next;
	}
	
	return(0);
}
