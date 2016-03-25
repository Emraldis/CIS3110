#include <string.h>
#include "functions.h"


Process * lineParse(char * input){
	Process * newProcess;
	char * tempString;
	
	newProcess = malloc(sizeof(Process));
	tempString = malloc(sizeof(char) * 256);
	
	tempString = strtok(input," ");
	
	if (tempString != NULL){
		newProcess.label = tempString;
	}
	
	tempString = strtok(NULL," ");
	if (tempString != NULL){
		newProcess->memoryReq = atoi(tempString);
	}
	
	return(newProcess);
}

Disk * addToBack(Disk * diskList, Process * prcIn){
	
	diskList->last->next = prcIn;
	diskList->last = prcIn;
	
	return(diskList);
}

Memory * addToMem(char * label, Process * prcIn, Memory * memoryList){
	int i;
	int j;
	
	j=0;
	while(memoryList->memoryArr[j]) != NULL)
		j++;
		if(j = memoryList->totalSize){
			break;
		}
	}
	if(memoryList->totalSize - j >= prcIn->memoryReq){
		for(i=j;i< prcIn->memoryReq;i++){
			memoryList->memoryArr[i] = (copyProcess(prcIn));
		}
	return(memoryList);
}

Process * copyProcess(Process * prcIn){
	Process * copy;
	
	copy = malloc(sizeof(Process));
	
	copy->memoryReq = prcIn->memoryReq;
	copy->label = prcIn->label;
	copy->next = NULL;
	
	return(copy);
}