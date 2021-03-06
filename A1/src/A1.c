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
#include "pipe.h"

int main (int argc, char ** argv){
    pid_t processID;
    int status = 0;
    char * input;
    char ** inputArr;
    char * temp;
    int i = 0;
    int j;
    FILE * filePtr;
    int redirect = 0;
    pid_t * pIDArr;
    int bProcess = 0;
    char * fileName;
    int k = 0;
    char * buffer;
    int len;
    char ** tempArr;
    int transfer[2];

    struct sigaction sigCatcher;

    sigCatcher.sa_sigaction = catchSig;

    buffer = malloc(sizeof(char)*256);
    input = malloc(sizeof(char)*256);
    inputArr = malloc(sizeof(char*)*256);
    pIDArr = malloc(sizeof(pid_t)*(bProcess + 1));
    tempArr = malloc(sizeof(char*)*256);

    printf("\n>> ");
    gets(input);
    while((strstr(input,"exit()") == NULL) && (strstr(input,"kill()") == NULL)){
        if(strlen(input) > 0){
            temp = strtok(input," ");
            i = 0;
            redirect = 0;
            do{
                inputArr[i] = temp;
                temp = strtok(NULL," ");
                i++;
            }while(temp != NULL);
            inputArr[i] = temp;
            for(j=0;j<i;j++){
                if((strcmp(inputArr[j],">") == 0) && (strlen(inputArr[j+1]) > 0)){
                    redirect = 1;
                    fileName = inputArr[j+1];
                    if(inputArr[j+2] != NULL){
                        while(inputArr[j+2] != NULL){
                            inputArr[j] = inputArr[j+2];
                            j++;
                        }
                    }else{
                        inputArr[j] = NULL;
                        inputArr[j+1] = NULL;
                    }
                    i = (i-2);
                }else if((strcmp(inputArr[j],"<") == 0) && (strlen(inputArr[j+1]) > 0)){
                    redirect = 0;
                    fileName = inputArr[j+1];
                    filePtr = fopen(fileName, "r");
                    i = j;
                    if(filePtr != NULL){
                        while(fgets(buffer,256,filePtr) != NULL){
                            temp = strtok(buffer, " ");
                            while(temp != NULL){
                                len = (strlen(temp));
                                for(k=0;k<len;k++){
                                    if(temp[k] == '\n'){
                                        temp[k] = '\0';
                                    }
                                }
                                inputArr[i] = temp;
                                temp = strtok(NULL, " ");
                                i++;
                            }
                        }
                        fclose(filePtr);
                    }else{
                        printf("\nFailed to redirect output, Invalid source file");
                        inputArr[i] = NULL;
                        inputArr[i+1] = NULL;
                    }
                    for(k=0;k<256;k++){
                        if(((inputArr[k] == fileName) && inputArr[k+1] == NULL)){
                            inputArr[k] = NULL;
                        }
                    }
                    for(k=0;k<i;k++){
                    }
                }else if((strcmp(inputArr[j],"|") == 0) && (strlen(inputArr[j+1]) > 0)){
                    redirect = -1;
                    inputArr[j] = NULL;
                    k=0;
                    while(inputArr[j+1] != NULL){
                        tempArr[k] = inputArr[j+1];
                        k++;
                        j++;
                    }
                    break;
                }else{
                    redirect = 0;
                }
            }
            processID = fork();
            if(processID >= 0){
                if(processID == 0){
                    if(redirect == 1){
                        filePtr = freopen(fileName,"w",stdout);
                        if(execvp(inputArr[0],inputArr) != -1){
                            fclose(filePtr);
                        }else{
                            fclose(filePtr);
                            printf("\nUnknown Command");
                        }
                    }else if(redirect == -1){
                        source(transfer,inputArr);
                        dest(transfer,tempArr);
                        close(transfer[0]);
                        close(transfer[1]);
                    }else{
                        if(execvp(inputArr[0],inputArr) == -1){
                            printf("\nUnknown Command");
                        }
                    }
                    exit(0);
                }else{
                    if((strstr("&",inputArr[(i-1)]))){
                        if(realloc(pIDArr,sizeof(pid_t)*(bProcess + 1)) != NULL){
                                pIDArr[bProcess] = processID;
                                bProcess++;
                                sigaction(SIGCHLD, &sigCatcher, NULL);
                            }
                        }else{
                            waitpid(processID, &status, 0);
                        }
                    }
            }else{
                printf("failed to fork\n");
            }
        }
        printf("\n>> ");
        gets(input);
    }
    for(j=0;j<bProcess;j++){
            printf("closing process. PID: %d",pIDArr[j]);
            waitpid(pIDArr[j], &status, 0);
    }
    free(inputArr);
    printf("\nlogout\n\n\n[Process Completed]\n");
}
