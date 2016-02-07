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
#include "fio.h"

int main (int argc, char ** argv){
    pid_t processID;
    int status = 0;
    char * input;
    char ** inputArr;
    char * temp;
    int i = 0;

    input = malloc(sizeof(char)*256);
    inputArr = malloc(sizeof(char*)*256);
    printf(">> ");
    gets(input);

    while((strstr(input,"exit()") == NULL) && (strstr(input,"kill()") == NULL)){
        temp = strtok(input," ");
        i = 0;
        do{
            inputArr[i] = temp;
            temp = strtok(NULL," ");
            i++;
        }while(temp != NULL);
        inputArr[i] = temp;
        processID = fork();
        if(processID >= 0){
            if(processID == 0){
                printf("Created new process. PID: %d\n", getpid());
                execvp(inputArr[0],inputArr);
                exit(0);
            }else{
                if((strstr("&",inputArr[(i-1)]))){
//                    waitpid(processID, &status, 0);
                    printf("had &");
                }else{
                    waitpid(processID, &status, 0);
                    printf("had no &");
                }
                printf("\nthe command \"%s\" was run\n", input);
            }
        }else{
            printf("failed to fork\n");
        }
        printf("\n>> ");
        gets(input);
    }
    free(inputArr);
}
