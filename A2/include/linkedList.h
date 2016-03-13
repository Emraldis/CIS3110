#include<stdio.h>
#include "fio.h"

Burst * moveToBack(Burst * list);

Burst * insertItem(Burst * insertLoc, Burst * item);

Burst * removeFirstBurst(Burst * list);

Thread * removeFirstThread(Thread * list);

Burst * copyThread(Burst * item);

Thread * copyThread(Thread * item);

Thread * addItem(Thread * list, Thread * item);
