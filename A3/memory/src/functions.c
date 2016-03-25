#include <string.h>
#include "functions.h"


Process * lineParse(char * input){
	Process * newProcess;
	char * tempString;
	
	newProcess = malloc(sizeof(Process));
	tempString = malloc(sizeof(char) * 256);
	
	tempString = strtok(input," ");
	
	if (tempString != NULL){
		newProcess->label = tempString;
	}
	
	tempString = strtok(NULL," ");
	
	return(newProcess);
}