#ifndef _AFELTHAM_HEADERH
#define _AFELTHAM_HEADERH
#include <stdio.h>
#include "structures.h"

Process * lineParse(char * input);	
Disk * addToBack(Disk * diskList);
Memory * firstFit(Process * prcIn, Memory * memoryList);
Memory * nextFit();
Memory * bestFit();
Memory * worstFit();
Process * copyProcess(Process * prcIn);
Disk * removeFromFront(Disk * diskList);

#endif