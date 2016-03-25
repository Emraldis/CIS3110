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

	tempProcess = malloc(sizeof(Process));
	
	fileName = argv[1];
	
	for(allocationMode=0;allocationMode<4;allocationMode++){	
		memory = malloc(sizeof(memory));
		disk = malloc(sizeof(disk));
		input = malloc(sizeof(char) * 256);
		memory->memoryArr = malloc(sizeof(Process *) * 128);
		disk->prcList = malloc(sizeof(Process));
		
		inputFile = fopen(fileName, "r");
		
		disk->prcList = NULL;
		
		/*printf("\nFile opened\n");
		getchar();*/
		
		while(fgets(input,256,inputFile) != NULL){
			/*printf("\nGoing to parse a line\n");
			getchar();*/
			tempProcess = lineParse(input);
			disk = addToBack(tempProcess->label,disk,copyProcess(tempProcess)));
			printf("\nFirst Process Label: %s, First Process Size: %d\n",disk->prcList->label,disk->prcList->memoryReq);
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
		
		free(memory->memoryArr);
		free(disk->prcList);
		free(input);
		free(disk);
		free(memory);
		
	}
	return(0);
}
