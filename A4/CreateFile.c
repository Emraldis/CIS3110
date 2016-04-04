#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>

int main (void){

FILE * output;
int i;


output = fopen("testfile.txt", "w");

for (i=0,i<1000000;i++){
	fputs("a",output);
}


	return(0);
}