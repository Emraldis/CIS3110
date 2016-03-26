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
	newProcess->version = 0;
	
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
	int j;
	
	j = 0;
	
	for(i=loc;i< (prcIn->memoryReq + loc);i++){
		if(memoryList->memoryArr[i] == NULL){
			prcIn->age = age;
			prcIn->version = j;
			memoryList->memoryArr[i] = copyProcess(prcIn);
			j++;
			//printf("\nallocating memory to slot %d",i);
		}else{
			printf("\nError allocating memory!");
		}
		//printf("\n%d",i);
		//getchar();
		prcIn->version = 0;
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
	copy->version = prcIn->version;
	
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
				//printf("\nLocation %d is unnocupied",(j+i));
			}else{
				//printf("\nLocation %d is occupied by %s",(j + i), memoryList->memoryArr[(j+i)]->label);
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
Memory * removeProcess(Memory * memoryList,Disk * diskList, int loc){
	int i;
	int age;
	
	age = -1;
	//printf("\nBeginning check for oldest Program");
	//getchar();
	for(i=loc;i < memoryList->totalSize;i++){
		if(memoryList->memoryArr[i] != NULL){
			if(age == -1){
				age = memoryList->memoryArr[i]->age;
			}
			if(memoryList->memoryArr[i]->age < age){
				//printf("\nNew oldest age was found:");
				age = memoryList->memoryArr[i]->age;
				//printf(" %d",age);
			}
		}
	}
	//printf("\nBeginning erase, searching for an age value of %d", age);
	for(i=loc;i < memoryList->totalSize;i++){
		if(memoryList->memoryArr[i] != NULL){
			//printf("\n@slot %d, filled by process %s, whose age value is %d ",i,memoryList->memoryArr[i]->label,memoryList->memoryArr[i]->age);
			if(memoryList->memoryArr[i]->age == age){
				//printf("\nage value found, deleting");
				if(memoryList->memoryArr[i]->version == 0){
					memoryList->memoryArr[i]->cycle--;
					if(memoryList->memoryArr[i]->cycle > 0){
						diskList = addToBack(diskList,memoryList->memoryArr[i]);
						//printf("\nProcess %s is being moved to disk.",memoryList->memoryArr[i]->label);
						//getchar();
					}else{
						//printf("\nProcess %s has completed.",memoryList->memoryArr[i]->label);
						//getchar();
					}
					memoryList->memoryArr[i] = NULL;
				}else {
					memoryList->memoryArr[i] = NULL;
				}
			}
		}
	}
	//printf("\nfinished!");
	//getchar();
	
	return(memoryList);
}
int nextFit(Memory * memoryList, int size,int loc){
	int  i;
	int j;
	
	j=0;
	if((memoryList->totalSize - loc) < size ){
		//printf("\nNot enough space in memory starting from here: %d", loc);
		loc = 0;
	}else if(loc == -1){
		loc = 0;
	}
	for(i=loc; i < memoryList->totalSize;i++){
		//printf("\nStarting search from %d",loc);
		while((j < size) && ((j+i) < memoryList->totalSize)){
			if(memoryList->memoryArr[j+i] == NULL){
				j++;
				//printf("\nLocation %d is unnocupied",(j+i));
			}else{
				//printf("\nLocation %d is occupied by %s",(j + i), memoryList->memoryArr[(j+i)]->label);
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

int bestFit(Memory * memoryList, int size){
	int i;
	int j;
	int differenceStore[2];
	
	differenceStore[0] = (memoryList->totalSize + 1);
	differenceStore[1] = -1;
	for(i=0;i < memoryList->totalSize;i++){
		j=0;
		if(memoryList->memoryArr[i] == NULL){
			//getchar();
			while(((j+i) < memoryList->totalSize) && (memoryList->memoryArr[j+i] == NULL)){
				j++;
			}
			if((memoryList->memoryArr[j+i] != NULL) && (j >= size)){
				//printf("\n for i = %d", i);
				if(j < differenceStore[0]){
					differenceStore[0] = j;
					differenceStore[1] = i;
					i = (i+j);
				}
			}
			if(((j+i) == memoryList->totalSize) && (j >= size)){
				//printf("\n for i = %d", i);
				return(i);
			}
		}
	}
	//printf("\nReturning %d", differenceStore[1]);
	return(differenceStore[1]);
}

int worstFit(Memory * memoryList, int size){
	int i;
	int j;
	int differenceStore[2];
	
	differenceStore[0] = (memoryList->totalSize + 1);
	differenceStore[1] = -1;
	for(i=0;i < memoryList->totalSize;i++){
		j=0;
		if(memoryList->memoryArr[i] == NULL){
			//getchar();
			while(((j+i) < memoryList->totalSize) && (memoryList->memoryArr[j+i] == NULL)){
				j++;
			}
			if((memoryList->memoryArr[j+i] != NULL) && (j >= size)){
				if(j > differenceStore[0]){
					//printf("\n for i = %d", i);
					differenceStore[0] = j;
					differenceStore[1] = i;
					i = (i+j);
				}
			}
			if(((j+i) == memoryList->totalSize) && (j >= size)){
				//printf("\n for i = %d", i);
				return(i);
			}
		}
	}
	//printf("\nReturning %d", differenceStore[1]);
	return(differenceStore[1]);
}
Stat * collectStats(Memory * memoryList, Stat * statInfo){
	int count;
	int countt;
	int i;
	int j;
	float tempFloat;
	
	count = 0;
	for(i=0;i< memoryList->totalSize; i++){
		j=0;
		if(memoryList->memoryArr[i] == NULL){
			while((memoryList->memoryArr[i+j] == NULL) && ((i + j) != memoryList->totalSize)){
				j++;
			}
			if(((memoryList->memoryArr[i+j] != NULL) || ((i + j) == memoryList->totalSize)) && ((i+j) > 0)){
				count++;
				i = (i + j);
				j=0;
			}
		}
	}
	statInfo->numHoles = count;
	statInfo->cumulativeHoles = (statInfo->cumulativeHoles + statInfo->numHoles);
	statInfo->avgHoles = (float)(statInfo->cumulativeHoles / statInfo->loads);
	count = 0;
	countt = 0;
	for(i=0;i<memoryList->totalSize;i++){
		if(memoryList->memoryArr[i] != NULL){
			count++;
			if(i != 0){
				if(memoryList->memoryArr[i-1] != NULL){
					if(strcmp(memoryList->memoryArr[i]->label,memoryList->memoryArr[(i-1)]->label) != 0){
						countt++;
					}
				}
			}else{
				if(memoryList->memoryArr[i] != NULL){
					countt++;
				}
			}
		}
	}/*
	printf("\nCount was: %d", count);
	tempFloat = (count/128.0);
	printf("\nMemory Usage should be: %f",tempFloat);*/
	statInfo->numProcesses = countt;
	statInfo->cumulativeProcesses = (statInfo->cumulativeProcesses + statInfo->numProcesses);
	statInfo->avgProcesses = (float)(statInfo->cumulativeProcesses / statInfo->loads);
	statInfo->percentMem = (float)((count / memoryList->totalSize) * 100);
	statInfo->cumulativeMem = (statInfo->cumulativeMem + statInfo->percentMem);
	statInfo->avgMem = (float)((statInfo->cumulativeMem / statInfo->loads) * 100);
	
	return(statInfo);
}