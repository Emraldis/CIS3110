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
	
	printf("\nstarting");
	getchar();
	currentBurst = list;
	if(list != NULL){
		printf("\nlist was not null");
		getchar();
		printf("\nCurrent burst num: %d", currentBurst->burstNum);
		getchar();
		while(currentBurst->nextBurst != NULL){
			currentBurst = currentBurst->nextBurst;
			printf("\nInterpolating, currentBurst = %d next Burst = %d CPU Time = %d",currentBurst->burstNum,currentBurst->nextBurst->burstNum, currentBurst->nextBurst->CPUTime);
			getchar();
		}
		if(currentBurst->nextBurst ==  NULL){
			printf("\nitem that we're tring to assign is: %d", item->burstNum);
			getchar();
			if(item == NULL){
				printf("\nItem appears to be NULL...");
			}
			currentBurst->nextBurst = item;
			if (currentBurst->nextBurst == item){
				printf("things are going smoothly");
			}
			currentBurst->nextBurst->nextBurst = NULL;
			printf("\nFinished Assigning");
			getchar();
			//printf("\nAdded Item, Burst number: %d = %d", currentBurst->nextBurst->burstNum,item->burstNum);
			if(currentBurst->nextBurst != NULL){
				if(currentBurst->nextBurst->nextBurst == NULL){
					printf("\nNext Item properly set");
				}else{
					printf("\nnope");
				}
		
			}else if(currentBurst->nextBurst == NULL){
				printf("\nwierd stuff's goin on");
			}
		}else{
			printf("\nERROR in addItem function\n");
			exit(0);
		}
	}else{
		printf("\nlist was null");
		getchar();
		list = item;
		printf("\nassigned list");
		getchar();
		getchar();
	}
	
	return(list);
}