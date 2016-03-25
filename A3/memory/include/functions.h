#include <stdio.h>
#include "structures.h"

Process * lineParse(char * input);	
Disk * addToBack(Disk * diskList, Process * prcIn);
Memory * firstFit(Process * prcIn, Memory * memoryList);
Memory * nextFit();
Memory * bestFit();
Memory * worstFit();
Process * copyProcess(Process * prcIn);
Disk * removeFromFront(Disk * diskList);
int fits(Memory * memoryList, int size);
