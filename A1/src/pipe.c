#include"pipe.h"

void catchSig(int sig, siginfo_t * signalInfo, void *hold){
    printf("\nSignal caught, PID: %d   Process Terminated",signalInfo->si_pid);
	if(signal == SIGINT){
	    waitpid(signal->si_pid,&status,0);
		exit(0);
	}
}
