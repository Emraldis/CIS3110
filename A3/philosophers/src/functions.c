#include "functions.h"

void * eat(void * id, void * timesEat){
	int i;
	int phlID
	int loop;
	
	phlID = (int) id;
	loop = (int) timesEat;
	
	for(i=0;i<loop;i++){
		printf("\nPhilosopher %d is thinking.",phlID);
		sem_wait(&semaphr);
		printf("\nPhilosopher %d is thinking.",phlID);
		sem_post(&semaphr);
		printf("\nPhilosopher %d is thinking.",phlID);
	}
	
	pthread_exit();
}