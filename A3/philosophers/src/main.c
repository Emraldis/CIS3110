#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include"functions.h"

sem_t semaphr;

int main (int argc, char * argv[]) {
	
	char * data;
	int i;
	int numPhilosophers;
	pthread_t threads[atoi(argv[1])];
	
	data = malloc(sizeof(char) * 256);
	
	numPhilosophers = atoi(argv[1]);
	
	sem_init(&semaphr,0,1);
	
	for(i=0;i<numPhilosophers;i++){	
		sprintf(data,"%d",i);
		strcat(data," ");
		strcat(data,argv[2]);
		pthread_create(&threads[i], NULL,(void *) &eat, ((void *)data));
		data = NULL;
	}
	
	sem_destroy(&semaphr);
	
	return(0);
	
}