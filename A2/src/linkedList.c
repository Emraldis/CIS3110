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
	
	currentBurst = list;
	
	while(currentBurst->nextBurst != NULL){
		currentBurst = currentBurst->nextBurst;
		printf("\nInterpolating, currentBurst = %d next Burst = %d CPU Time = %d",currentBurst->burstNum,currentBurst->nextBurst->burstNum, currentBurst->nextBurst->CPUTime);
		getchar();
	}
	if(currentBurst->nextBurst ==  NULL){
		currentBurst->nextBurst = item;
		item->nextBurst = NULL;
		printf("\nAdded Item, Burst number: %d = %d", currentBurst->nextBurst->burstNum,item->burstNum);
		if((currentBurst->nextBurst->nextBurst == NULL) && (currentBust->nextBurst != NULL)){
			printf("\nNext Item properly set");
		}else{
			printf("\nnope");
		}
		
	}else{
		printf("\nERROR in addItem function\n");
		exit(0);
	}
	
	return(list);
}