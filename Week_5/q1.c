/*Write a C program to block a parent process until the child completes using a wait system call.*/

#include "header.h"
void main() {
    int status;
    pid_t pid;
    pid = fork();
    if(pid == -1)
        write(2,"ERROR child not created",23);
    else if (pid == 0){
        write(1,"\nI'm the child!",14);
        for (int i=0;i<1000;i++);
        exit(0);
    }
    else if (pid > 0){
        wait(&status); //block until the child process terminates
        write(1,"\nI'm the parent!",15); 
        printf("\nChild returned: %d\n",status);
    }
}
