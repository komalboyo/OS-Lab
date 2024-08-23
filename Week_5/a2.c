/*Modify a1.c to include wait(&status) in the parent and to display the exit return code (leftmost byte of status) of the child.*/

#include "header.h"

int main() {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Original Parent PID: %d\n", getppid());
        sleep(10); 
        printf("After parent termination:\n"); // After sleep, check the new parent PID
        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());
        exit(42); // Exit with a specific return code (e.g., 42)
    } else {
        printf("Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        wait(&status);
        int exit_code = WEXITSTATUS(status);
        printf("Child exit code: %d\n", exit_code);
        exit(0);
    }

    return 0;
}

