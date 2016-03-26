#include "functions.h"

void * eat(void * data[2]){
	int i;
	int phlID
	int loop;
	
	phlID = (int) data[0];
	loop = (int) data[1];
	
	for(i=0;i<loop;i++){
		printf("\nPhilosopher %d is thinking.",phlID);
		sem_wait(&semaphr);
		printf("\nPhilosopher %d is thinking.",phlID);
		sem_post(&semaphr);
		printf("\nPhilosopher %d is thinking.",phlID);
	}
	
	pthread_exit();
}