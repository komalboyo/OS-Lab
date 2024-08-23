/*Write a program to create a child process. Display the process IDs of the process, parent and child (if any) in both the parent and child processes.*/

#include "header.h"

int main() {
    int status;
    pid_t pid, grandchild_pid;
    pid = fork();
    if(pid == -1)
        printf("\nERROR child not created");
    else if (pid == 0){ //new process created
        printf("\nI'm the child!");
        printf("\npid is %d\nppid is %d\n", getpid(), getppid());
        grandchild_pid = fork(); // Create a new grandchild process.

        if (grandchild_pid == -1) {
            printf("\nERROR grandchild not created");
        } else if (grandchild_pid == 0) {
            // This block is executed by the grandchild process.
            printf("\nI'm the grandchild!");
            printf("\npid is %d\nppid is %d\n", getpid(), getppid());
            exit(0);
        } else {
            // Child process waits for the grandchild to terminate.
            wait(&status);
        }

        exit(0); // Exit the child process.
    }
    else{
        wait(&status);
        printf("\nI'm the parent!");
        printf("\npid is %d\nppid is %d\n", getpid(), getppid());
        // id of grandparent process ie shell that initialted execution of program
    }
}
