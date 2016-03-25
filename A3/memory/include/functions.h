#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include "strutures.h"

Process * lineParse(char * input);	
Disk * addToBack(Disk * diskList);
Memory * addToMem(char * label, Process * prcIn, Memory * memoryList);

#endif