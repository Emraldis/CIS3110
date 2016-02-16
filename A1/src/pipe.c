#include"pipe.h"

void catchSig(int sig, siginfo_t * signalInfo, void *hold){
    int status = 0;
    waitpid(signalInfo->si_pid, &status, 0);
    if(sig == SIGINT){
    exit(0);
    }
}

void source(int transfer[], char ** cmdArr){
    int processID;
    processID = fork();
    if(processID >= 0){
        if(processID == 0){
            dup2(transfer[1],1);
            close(transfer[0]);
            if(execvp(cmdArr[0],cmdArr) == -1){
                printf("\nUnknown command");
            }
        }
    }
}

void dest(int transfer[], char ** cmdArr){
    int processID;
    processID = fork();
    if(processID >= 0){
        if(processID == 0){
            dup2(transfer[0],0);
            close(transfer[1]);
            if(execvp(cmdArr[0],cmdArr) == -1){
                printf("\nUnknown command");
            }
        }
    }
    
}
