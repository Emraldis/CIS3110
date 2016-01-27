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

int main (void){
    pid_t processID;
    int status = 0;
    char* testString = "test";

    processID = fork();

    if(processID >= 0){
        if(processID == 0){
            printf("this is the child process. My PID is %d\n", getpid());
            printf("%s\n", testString);
            exit(0);
        }else{
            printf("this is the parent process. My PID is %d\n", getpid());
            waitpid(processID, &status, 0);
            printf("%s\n My child has quit\n", testString);
        }
    }else{
        printf("failed to fork\n");
    }
}
