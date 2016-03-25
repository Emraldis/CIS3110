#include <string.h>
#include "functions.h"


Process * lineParse(char * input){
	Process * newProcess;
	char * tempString;
	
	newProcess = malloc(sizeof(Process));
	tempString = malloc(sizeof(char) * 256);
	tempString = strtok(input," ");
	newProcess->label = malloc(sizeof(char) * 256);
	
	
	if (tempString != NULL){
		strcpy(newProcess->label,tempString);
	}
	
	tempString = strtok(NULL,"\0");
	if (tempString != NULL){
		newProcess->memoryReq = atoi(tempString);
	}
	
	return(newProcess);
}

Disk * addToBack(Disk * diskList, Process * prcIn){
	if(diskList->prcList != NULL){
		printf("\nDisk is not empty\n");
		printf("\nTesting Label: %s\n",diskList->prcList->label);
		diskList->last->next = prcIn;
		diskList->last = diskList->last->next;
	}else if(diskList->prcList == NULL){
		printf("\nDisk was empty\n");
		if(prcIn != NULL){
			diskList->prcList = prcIn;
			diskList->last = diskList->prcList;
		}else{
			printf("\nProcess was NULL");
			getchar();
		}
	}
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