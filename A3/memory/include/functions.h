#include <stdio.h>
#include "structures.h"

Process * lineParse(char * input);	
Disk * addToBack(Disk * diskList, Process * prcIn);
Memory * insert(Process * prcIn, Memory * memoryList,int loc,int age);
int nextFit(Memory * memoryList, int size,int loc);
int bestFit();
int worstFit();
Process * copyProcess(Process * prcIn);
Disk * removeFromFront(Disk * diskList);
int firstFit(Memory * memoryList, int size);
Memory * removeProcess(Memory * memoryList, Disk * diskList,int loc);
