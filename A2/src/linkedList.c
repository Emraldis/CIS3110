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

Burst * addItem(Burst * list, Burst * item){
	
	Burst * currentBurst;
	Burst * tempBurst;

	tempBurst = item;
	tempBurst->nextBurst = NULL;
	
	printf("\nItem's process number: %d", item->processNum);
	
	if(list != NULL){
		currentBurst = list;
		while(currentBurst->nextBurst != NULL){
			currentBurst = currentBurst->nextBurst;
		}
		if(currentBurst->nextBurst ==  NULL){
			currentBurst->nextBurst = tempBurst;
		}else{
			printf("\nERROR in addItem function\n");
			exit(0);
		}
	}else{
		list = tempBurst;
	}
	
	return(list);
}