#include <string.h>
#include "functions.h"


Process * lineParse(char * input){
	Process * newProcess;
	char * tempString;
	
	newProcess = malloc(sizeof(Process));
	tempString = malloc(sizeof(char) * 256);
	/*
	printf("\nStarting parse\n");
	getchar();
	*/
	tempString = strtok(input," ");
	
	/*printf("\nParsed first chunk, tempString = %s\n", tempString);
	getchar();*/
	
	if (tempString != NULL){
		newProcess->label = tempString;
		//printf("\nValue Stored: %s\n", newProcess->label);
		//getchar();
	}
	
	tempString = strtok(NULL,"\0");
	/*printf("\nParsed second chunk, tempString = %s\n", tempString);
	getchar();*/
	if (tempString != NULL){
		newProcess->memoryReq = atoi(tempString);
		/*printf("\nValue Stored: %d\n", newProcess->memoryReq);
		getchar();*/
	}
	/*printf("\nFinished!\n");
	getchar();*/
	
	return(newProcess);
}

Disk * addToBack(Disk * diskList, Process * prcIn){
	/*printf("\nAdding to disk\n");
	getchar();*/
	if(diskList->prcList != NULL){
		/*printf("\nDisk is not empty\n");
		getchar();*/
		printf("\nFirst Process Label: %s\n",diskList->prcList->label);
		diskList->last->next = copyProcess(prcIn);
		diskList->last = diskList->last->next;
	}else if(diskList->prcList == NULL){
		/*printf("\nDisk was empty\n");
		getchar();*/
		if(prcIn != NULL){
			/*printf("\nProcess was not NULL");
			getchar();*/
			diskList->prcList = copyProcess(prcIn);
			diskList->last = diskList->prcList;
		}else{
			printf("\nProcess was NULL");
			getchar();
		}
	}
	/*printf("\nFinished!\n");
	getchar();*/
	return(diskList);
}

Memory * firstFit(Process * prcIn, Memory * memoryList){
	int i;
	int j;
	
	j=0;
	while((memoryList->memoryArr[j]) != NULL){
		j++;
		if(j == memoryList->totalSize){
			break;
		}
	}
	if(memoryList->totalSize - j >= prcIn->memoryReq){
		for(i=j;i< prcIn->memoryReq;i++){
			memoryList->memoryArr[i] = (copyProcess(prcIn));
		}
	return(memoryList);
	}else{
		return(NULL);
	}
}

Process * copyProcess(Process * prcIn){
	Process * copy;
	
	copy = malloc(sizeof(Process));
	
	copy->memoryReq = prcIn->memoryReq;
	copy->label = prcIn->label;
	copy->next = NULL;
	copy->cycle = prcIn->cycle;
	copy->age = prcIn->age;
	
	return(copy);
}

Disk * removeFromFront(Disk * diskList){
	
	diskList->prcList = diskList->prcList->next;
	
	return(diskList);
}