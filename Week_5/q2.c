/*Write a C program to load the binary executable of the previous program in a child process using the exec system call.*/

#include "header.h"

int main(){
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        perror("fork failed");
	exit(1);
    }
    else if(pid == 0){
    // This block is executed by the child process.
        execlp("./q1", "q1", NULL); 
        perror("execlp failed"); // Print an error message if execlp() fails.
        exit(1);
    }
    else{
        wait (NULL); //status of child not retrieved
        write(1,"Complete\n",10);
        exit(0);
    }
}
