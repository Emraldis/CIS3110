#include "linkedList.h"

Burst * moveToBack(Burst * list){
	
	Burst * tempBurst;
	Burst * currentBurst;
	
	tempBurst = list;
	currentBurst = list->nextBurst;
	list = currentBurst;
	while(currentBurst->nextBurst != NULL){
		currentBurst = currentBurst->nextBurst;
	}
	if(currentBurst->nextBurst == NULL){
		currentBurst->nextBurst = tempBurst;
	}else{
		printf("\nERROR in moveToBack function\n");
		exit(0);
	}
	
	return(list);
	
}

Burst * insertItem(Burst * insertLoc, Burst * item){

	Burst * tempBurst;
	
	tempBurst = insertLoc->nextBurst;
	insertLoc->nextBurst = item;
	item->nextBurst = tempBurst;

	return(insertLoc);

}

Burst * copyBurst(Burst * item){

	Burst * copy;
	
	copy = malloc(sizeof(Burst));

	copy->burstNum = item->burstNum;
	copy->threadNum = item->threadNum;
	copy->processNum = item->processNum;
	copy->CPUTime = item->CPUTime;
	copy->IOTime = item->IOTime;
	copy->readyTime = item->readyTime;
	copy->entryTime = item->entryTime;
	copy->exitTime = item->exitTime;
	copy->remainingTime = item->remainingTime;
	copy->nextBurst = item->nextBurst;
	
	return(copy);
	
}

Thread * copyThread(Thread * item){

	Thread * copy;
	
	copy = malloc(sizeof(Thread));
	
	copy->threadNum = item->threadNum;
	copy->processNum = item->processNum;
	copy->arrivalTime = item->arrivalTime;
	copy->numBursts = item->numBursts;
	copy->nextThread = item->nextThread;
	copy->nextBurst = item->nextBurst;
	copy->waitTime = item->waitTime;
	
	return(copy);
	
}

Thread * addItem(Thread * list, Thread * item){
	
	Thread * currentThread;
	Thread * tempThread;

	tempThread = copyThread(item);
	tempThread->nextThread = NULL;
	
	//printf("\nItem's process number: %d", item->processNum);
	
	if(list != NULL){
		currentThread = list;
		while(currentThread->nextThread != NULL){
			currentThread = currentThread->nextThread;
		}
		if(currentThread->nextThread ==  NULL){
			currentThread->nextThread = tempThread;
		}else{
			printf("\nERROR in addItem function\n");
			exit(0);
		}
	}else{
		list = tempThread;
	}
	
	return(list);
}

Thread * removeFirstThread(Thread * list){

	return(list->nextThread);

}

Burst * removeFirstBurst(Burst * list){
	
	return(list->nextBurst);
	
}
