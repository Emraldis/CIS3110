#include <stdio.h>
#include <string.h>
#include "fio.h"
#include "linkedList.h"
#include "process.h"

int main void (int argc, char ** argv){

    char * fileName;
    int processTrans;
    int threadTrans;
    char * input;
    int processNum;
    int threadNum;
    char * tempString;
    int i;
    FILE * file;
    process ** processArr;

    fileName = argv[argc];
    file * fopen(fileName,"r");
    while(fgets(input,256,file) != NULL){
        tempString = strtok(input, " ");
        if(tempString != NULL){
            processNum = atoi(tempString);
        }
        tempString = strtok(input, " ");
        if (tempString != NULL){
            processTrans = atoi(tempString);
        }
        tempString = strtok(input, " ");
        if (tempString != NULL){
            threadTrans = atoi(tempString);
        }
        for(i=0;i<processNum;i++){
            if(fgets(input,256,file) != NULL){
            }
        }
    }

    return();
}
