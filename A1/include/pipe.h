//#ifndef _AFELTHAM_HEADERH
//#define _AFELTHAM_HEADERH
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>


void catchSig(int sig, siginfo_t * signalInfo, void *hold);


//#endif
