#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include"functions.h"

sem_t semaphr;

int main (int argc, char * argv[]) {
	
	int data[2];
	int i;
	pthread_t threads[atoi(argv[1])];
	
	data[1] = (atoi(argv[2]));
	
	sem_init(&semaphr,0,1);
	
	for(i=0;i<numPhilosophers;i++){
		data[0] = i;
		pthread_create(&threads[i], NULL, eat, ((void *)data));
	}
	
	sem_destroy(&semaphr);
	
	return(0);
	
}