#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>

int main (void){
	int i;
	char * temp;
	FILE * inputFile;
	FILE * outputFile;
	double timeStart;
	double timeEnd;
	double difference;
	struct timeval start;
	struct timeval end;
	char * outputString;

	i = 100;
	outputString = malloc(sizeof(char) * 256);
	temp = malloc(sizeof(char) * i);
	do{
		inputFile = fopen("testfile.txt","r");
		gettimeofday(&start, NULL);
		fgets(temp,i,inputFile);
		printf("\nread %d bytes",i);
		gettimeofday(&end, NULL);
		fclose(inputFile);
		timeStart = start.tv_sec + (double)start.tv_usec / 1000000.0;
		timeEnd = end.tv_sec + (double)end.tv_usec / 1000000.0;
		difference = timeEnd-timeStart;
		sprintf(outputString,"Start time: %f End time: %f Time elapsed: %f",timeStart, timeEnd, difference);
		outputFile = fopen("output.txt","a");
		fputs(outputString,outputFile);
		fclose(outputFile);
		if(i<1000000){
			i = (i + 100);	
			temp = realloc(temp,(sizeof(char) * i));
			//getchar();
		}else{
			break;
		}
	}while(temp != NULL);
	printf("\n");
	free(temp);
	free(outputString);

	return(0);
}