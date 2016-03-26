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
		diskList->last->next = prcIn;
		diskList->last = diskList->last->next;
	}else if(diskList->prcList == NULL){
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

Memory * insert(Process * prcIn, Memory * memoryList,int loc){
	int i;
	
	for(i=loc;i< prcIn->memoryReq;i++){
		if(memoryList->memoryArr[i] == NULL){
			memoryList->memoryArr[i] = copyProcess(prcIn);
		}
		//printf("\n%d",i);
		//getchar();
	}
	
	return(memoryList);
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
int firstFit(Memory * memoryList, int size){
	int  i;
	int j;
	
	j=0;
	for(i=0; i < memoryList->totalSize;i++){
		while((j < size) && ((j+i) < memoryList->totalSize)){
			if(memoryList->memoryArr[j+i] == NULL){
				j++;
			}else{
				j=0;
			}
		}
		if(j == size){
			return(i);
		}
		printf("\n%d",i);
	}
	return(-1);
	
}