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
	
	memory = malloc(sizeof(memory));
	disk = malloc(sizeof(disk));
	input = malloc(sizeof(char) * 256);
	memory->memoryArr = malloc(sizeof(Process *) * 128);
	disk->prcList = malloc(sizeof(Process));
	
	fileName = argv[1];
	
	for(allocationMode=0;allocationMode<4;allocationMode++){
		inputFile = fopen(fileName, "r");
		
		disk->prcList = NULL;
		
		/*printf("\nFile opened\n");
		getchar();*/
		
		while(fgets(input,256,inputFile) != NULL){
			/*printf("\nGoing to parse a line\n");
			getchar();*/
			disk = addToBack(disk,copyProcess(lineParse(input)));
			printf("\nFirst Process Label: %s\n",disk->prcList->label);
			/*printf("\nParsed a line\n");
			getchar();*/
		}
		fclose(inputFile);
		currentProcess = disk->prcList;
		while(currentProcess != NULL){
			printf("\nName: %s\nSize: %d\n",currentProcess->label,currentProcess->memoryReq);
			currentProcess = currentProcess->next;
			//getchar();
		}
		printf("\n______________________________________________________________________________________________________________\n");
		
	}
	return(0);
}
