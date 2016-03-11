#include <stdio.h>
#include <string.h>
#include "fio.h"
#include "linkedList.h"
#include "process.h"

int main (int argc, char * argv[]){

    char * fileName;
    int processTrans;
    int threadTrans;
    char * input;
    int processNum;
    int threadNum;
    char * tempString;
    int i;
    int j;
    int k;
    FILE * inputFile;
    Process * readyQ;
    Process * currentProcess;
    Process * ProcessList;

    input = malloc(sizeof(char)*256);

    fileName = argv[1];
    printf("\nDataFile: %s",fileName);
    inputFile = fopen(fileName,"r");
	if(fgets(input,256,inputFile) != NULL){
        tempString = strtok(input, " ");
        if(tempString != NULL){
            processNum = atoi(tempString);
        }
        tempString = strtok(NULL, " ");
        if (tempString != NULL){
            processTrans = atoi(tempString);
        }
        tempString = strtok(NULL, " ");
        if (tempString != NULL){
            threadTrans = atoi(tempString);
        }
        printf("\nNumber of Processes: %d\n Overhead between Threads of the same Process: %d\nOverhead between Threads of different Processes: %d\n",processNum,processTrans,threadTrans);
		if(fgets(input,256,inputFile)){
			ProcessList = createProcess(input);
			currentProcess = ProcessList;
		}
        for(i=0;i<processNum;i++){
        	printf("Process Number: %d\n",(currentProcess->processNum));
            if(fgets(input,256,inputFile) != NULL){
                currentProcess->nextProcess = createProcess(input);
				currentProcess = currentProcess->nextProcess;
            }
        }
    }

    return(0);
}
