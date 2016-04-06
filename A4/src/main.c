#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>

int main (int argc, char * argv[]){
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
	int a;
	int j;

	a = atoi(argv[1]);
	i = 1000;
	j = 0;
	outputString = malloc(sizeof(char) * 1000);
	temp = malloc(sizeof(char) * i);
	outputFile = fopen("size.txt","w");
	fclose(outputFile);
	outputFile = fopen("start.txt","w");
	fclose(outputFile);
	outputFile = fopen("end.txt","w");
	fclose(outputFile);
	do{
		if(a == 1){
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
			sprintf(outputString,"%f\n",difference);
			outputFile = fopen("difference.txt","a");
			fputs(outputString,outputFile);
			fclose(outputFile);
			if(i<1000000){
				i = (i + 1000);	
				temp = realloc(temp,(sizeof(char) * i));
				//getchar();
			}else{
				break;
			}
		}else if(a == 2){
			j++;
			inputFile = fopen("testfile.txt","r");
			gettimeofday(&start, NULL);
			fgets(temp,1000,inputFile);
			gettimeofday(&end, NULL);
			fclose(inputFile);
			timeStart = start.tv_sec + (double)start.tv_usec / 1000000.0;
			timeEnd = end.tv_sec + (double)end.tv_usec / 1000000.0;
			difference = timeEnd-timeStart;
			sprintf(outputString,"%d\n",j);
			outputFile = fopen("occurence.txt","a");
			fputs(outputString,outputFile);
			fclose(outputFile);
			sprintf(outputString,"%f\n",difference);
			outputFile = fopen("difference2.txt","a");
			fputs(outputString,outputFile);
			fclose(outputFile);
			if(j >= 100){
				break;
			}
		}
		}else{
			printf("\nError encountered, Quitting\n");
			return(0);
		}
	}while(temp != NULL);
	printf("\n");
	free(temp);
	free(outputString);

	return(0);
}