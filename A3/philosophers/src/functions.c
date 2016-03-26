#include "functions.h"

void * eat(void * id, void * timesEat){
	int i;
	
	for(i=0;i<timesEat;i++){
		printf("\nPhilosopher %d is thinking.",id);
		sem_wait(&semaphr);
		printf("\nPhilosopher %d is thinking.",id);
		sem_post(&semaphr);
		printf("\nPhilosopher %d is thinking.",id);
	}
	
	pthread_exit();
}