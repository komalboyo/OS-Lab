/*Create a zombie (defunct) child process (a child with exit() call, but no corresponding wait() in the sleeping parent) and allow the init process to adopt it (after parent terminates). Run the process as a background process and run the “ps” command.*/

#include "header.h"

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
	exit(1);
    }
    else if (pid == 0) {
        printf("\nI'm the child!");
        printf("\npid is %d\nppid is %d", getpid(), getppid());
        exit(0);
    }
    else { 
        sleep(100);
        printf ("\nComplete\n");
        exit(0);
    }
}

// run code
// ctrl z
// bg
// ps
