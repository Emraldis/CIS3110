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
	outputFile = fopen("size.txt","w");
	fclose(outputFile);
	outputFile = fopen("start.txt","w");
	fclose(outputFile);
	outputFile = fopen("end.txt","w");
	fclose(outputFile);
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
		sprintf(outputString,"%d\n",i);
		outputFile = fopen("size.txt","a");
		fputs(outputString,outputFile);
		fclose(outputFile);
		sprintf(outputString,"%f\n",timeStart);
		outputFile = fopen("start.txt","a");
		fputs(outputString,outputFile);
		fclose(outputFile);
		sprintf(outputString,"%f\n",timeEnd);
		outputFile = fopen("end.txt","a");
		fputs(outputString,outputFile);
		fclose(outputFile);
		sprintf(outputString,"%f\n",difference);
		outputFile = fopen("difference.txt","a");
		fputs(outputString,outputFile);
		fclose(outputFile);
		if(i<100000){
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