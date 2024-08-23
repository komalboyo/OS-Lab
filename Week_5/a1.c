/*Create an orphan process (parent dies before child – adopted by “init” process) and display the PID of the parent of the child before and after it becomes orphan. Use sleep(n) in the child to delay the termination.*/

#include "header.h"

int main() {
    pid_t pid, parent_pid;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        parent_pid = getppid(); // Store the parent PID
        printf("here\n");
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Original Parent PID: %d\n", parent_pid);
        // Sleep to allow time for the parent process to terminate and child to become orphaned
        sleep(10);

        // After sleep, check the new parent PID
        parent_pid = getppid();
        printf("After parent termination:\n");
        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", parent_pid);

        exit(0);
    } else {
        printf("Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
	//sleep(10);
        // Parent terminates before the child to make it an orphan
        exit(0);
    }

    return 0;
}

