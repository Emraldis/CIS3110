#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

typedef struct Philosopher{
	int ID;
	int eatCount;
}Phl;

void * eat(void * ptr);

sem_t semaphr;


int main (int argc, char * argv[]) {
	
	int i;
	int numPhilosophers;
	Phl * philoStruct;
	pthread_t threads[atoi(argv[1])];
	
	philoStruct = malloc(sizeof(Phl));
	
	numPhilosophers = atoi(argv[1]);
	
	sem_init(&semaphr,0,1);
	
	philoStruct->eatCount = atoi(argv[2]);
	
	printf("\nNum of philosophers: %d", numPhilosophers);
	
	for(i=0;i<numPhilosophers;i++){	
		philoStruct->ID = (i+1);
		printf("\nCreating thread!");
		if(pthread_create(&threads[i], NULL, eat, ((void *)&philoStruct)) != 0){
			printf("\nError making thread");
		}else{
			printf("\nFinished creating thread!");
		}
	}
	
	sem_destroy(&semaphr);
	
	return(0);
	
}

void * eat(void * ptr){
	int i;
	int phlID;
	int loop;
	
	//printf("\ntest");

	Phl * data = (Phl *)ptr;
	phlID = (int)data->ID;
	loop = (int)data->	eatCount;
	//fflush(stdout);
	
	for(i=0;i<loop;i++){
		printf("\nPhilosopher %d is thinking.",phlID);
		printf("\ntest");
		sem_wait(&semaphr);
		printf("\nPhilosopher %d is thinking.",phlID);
		sem_post(&semaphr);
		printf("\nPhilosopher %d is thinking.",phlID);
	}
	
	pthread_exit(NULL);
}