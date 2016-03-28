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
	Phl ** philoStruct;
	pthread_t threads[atoi(argv[1])];
	
	philoStruct = malloc(sizeof(Phl *) * (atoi(argv[1])));
	
	numPhilosophers = atoi(argv[1]);
	
	sem_init(&semaphr,0,1);
	printf("\ntest");
	fflush(stdout);
	for(i=0;i < numPhilosophers; i++){
		printf("\ntesting");
		fflush(stdout);
		philoStruct[i]->eatCount = atoi(argv[2]);
	}
	printf("\ntest");
	fflush(stdout);
	
	//printf("\nEat count: %d",philoStruct[]eatCount);
	//printf("\nNum of philosophers: %d", numPhilosophers);
	
	for(i=0;i<numPhilosophers;i++){	
		printf("\ntest");
		fflush(stdout);
		philoStruct[i]->ID = (i+1);
		printf("\nCreating thread, ID is %d||%d",(i+1),philoStruct[i]->ID);
		fflush(stdout);
		if(pthread_create(&threads[i], NULL, eat, ((void *) philoStruct)) != 0){
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

	Phl * data = (Phl *)ptr;
	phlID = (int)data->ID;
	loop = (int)data->eatCount;
	printf("\n%d",loop);
	printf("\nID:%d",phlID);
	
	for(i=0;i<loop;i++){
		printf("\nPhilosopher %d is thinking.",phlID);
		printf("\ntest");
		fflush(stdout);
		sem_wait(&semaphr);
		printf("\nPhilosopher %d is thinking.",phlID);
		sem_post(&semaphr);
		printf("\nPhilosopher %d is thinking.",phlID);
	}
	
	pthread_exit(NULL);
}