#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>

int main (void){
	int i;
	char * temp;
	FILE * inputFile;
	double timeStart;
	double timeEnd;
	double difference;
	struct timeval start;
	struct timeval end;

	i = 10;
	
	do{
		inputFile = fopen("testfile.txt","r");
		inpugettimeofday(&start, NULL);
		fgets(temp,i,inputFile);
		printf("\nread %d bytes",i);
		gettimeofday(&end, NULL);
		fclose(inputFile);
		timeStart = start.tv_sec + (double)start.tv_usec / 1000000.0;
		timeEnd = end.tv_sec + (double)end.tv_usec / 1000000.0;
		difference = timeEnd-timeStart;
		printf("Start time: %f End time: %f Time elapsed: %f",timeStart, timeEnd, difference);
		if(i<1000000){
			i = (i*10);
		}
	}while(temp != NULL);

	return(0);
}