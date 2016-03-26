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
	newProcess->cycle = 3;
	
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

Memory * insert(Process * prcIn, Memory * memoryList,int loc, int age){
	int i;
	
	for(i=loc;i< (prcIn->memoryReq + loc);i++){
		if(memoryList->memoryArr[i] == NULL){
			prcIn->age = age;
			memoryList->memoryArr[i] = copyProcess(prcIn);
			printf("\nallocating memory to slot %d",i);
		}else{
			printf("\nError allocating memory!");
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
				printf("\nLocation %d is unnocupied",(j+i));
			}else{
				printf("\nLocation %d is occupied by %s",(j + i), memoryList->memoryArr[(j+i)]->label);
				//getchar();
				j=0;
				i++;
			}
		}
		if(j == size){
			return(i);
		}
		//printf("\n%d",i);
	}
	return(-1);
}
Memory * removeProcess(Memory * memoryList){
	int i;
	int age;
	
	age = 0;
	printf("\nBeginning check for oldest Program");
	getchar();
	for(i=0;i < memoryList->totalSize;i++){
		if(memoryList->memoryArr[i] != NULL){
			printf("\nCurrent oldest age: %d @ array number: %d", age,i);
			getchar();
			if(memoryList->memoryArr[i]->age < age){
				printf("\nnNew oldest age was found:");
				age = memoryList->memoryArr[i]->age;
				printf(" %d",age);
			}
		}
	}
	printf("\nBeginning erase, searching for an age value of %d", age);
	getchar();
	for(i=0;i < memoryList->totalSize;i++){
		if(memoryList->memoryArr != NULL){
			printf("\n@slot %d, filled by process %s, whose age value is %d ",i,memoryList->memoryArr[i]->label,memoryList->memoryArr[i]->age);
			getchar();
			if(memoryList->memoryArr[i]->age == age){
				printf("\nage value found, deleting");
				getchar();
				memoryList->memoryArr[i] = NULL;
			}
		}
	}
	
	return(memoryList);
}
