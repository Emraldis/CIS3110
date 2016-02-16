#include"pipe.h"

void catchSig(int sig, siginfo_t * signalInfo, void *hold){
    int status = 0;
    printf("\nSignal caught, PID: %d   Process Terminated",signalInfo->si_pid);
    waitpid(signalInfo->si_pid, &status, 0);
    if(sig == SIGINT){
    exit(0);
    }
}

void pipeSig(int sig, siginfo_t * signalInfo, void *hold){
    
}
