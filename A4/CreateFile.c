#include "stdio.h"
#include "stdlib.h"

int main (void){

	FILE * output;
	int i;

	output = fopen("testfile.txt", "w");

	for (i=0;i<1000000;i++){
		fputs("a",output);
	}

	fclose(output);

	return(0);
}