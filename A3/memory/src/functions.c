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
	
	return(newProcess);
}

Disk * addToBack(Disk * diskList, Process * prcIn){
	Process * currentProcess;
	
	currentProcess = diskList->last;
	
	return(diskList);
}

Memory * addToMem(char * label, Process * prcIn, Memory * memoryList){
	
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