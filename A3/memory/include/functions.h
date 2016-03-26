#include <stdio.h>
#include "structures.h"

Process * lineParse(char * input);	
Disk * addToBack(Disk * diskList, Process * prcIn);
Memory * insert(Process * prcIn, Memory * memoryList,int loc,int age);
Memory * nextFit();
Memory * bestFit();
Memory * worstFit();
Process * copyProcess(Process * prcIn);
Disk * removeFromFront(Disk * diskList);
int firstFit(Memory * memoryList, int size);
Memory * removeProcess(Memory * memoryList, Disk * diskList);
