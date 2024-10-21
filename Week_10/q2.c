#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TIME_QUANTUM 4

// Structure to represent a process
struct process {
    int pid;           // Process ID
    int arrival_time;  // Arrival time of the process
    int burst_time;    // Total burst time
    int remaining_time;// Time remaining for process to complete
    int queue_level;   // Which queue this process is in
    struct process *next;
};

typedef struct process Process;
typedef Process* ProcessPtr;

// Global head pointers for the three queues
ProcessPtr queue1 = NULL;
ProcessPtr queue2 = NULL;
ProcessPtr queue3 = NULL;

// Function to create a new process
ProcessPtr createProcess(int pid, int arrival_time, int burst_time) {
    ProcessPtr newProcess = (ProcessPtr) malloc(sizeof(Process));
    newProcess->pid = pid;
    newProcess->arrival_time = arrival_time;
    newProcess->burst_time = burst_time;
    newProcess->remaining_time = burst_time;
    newProcess->queue_level = 1; // All processes start in Queue 1
    newProcess->next = NULL;
    return newProcess;
}

// Function to insert a process into a queue
void insertProcess(ProcessPtr *queue, ProcessPtr process) {
    if (*queue == NULL) {
        *queue = process;
    } else {
        ProcessPtr temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = process;
    }
}

// Function to remove the first process from a queue
ProcessPtr removeProcess(ProcessPtr *queue) {
    if (*queue == NULL) {
        return NULL;
    }
    ProcessPtr process = *queue;
    *queue = (*queue)->next;
    process->next = NULL;
    return process;
}

// Function to simulate Round Robin scheduling for Queue 1
void scheduleQueue1() {
    if (queue1 == NULL) {
        return;
    }

    ProcessPtr currentProcess = removeProcess(&queue1);
    printf("Queue 1 (Round Robin): Running process %d\n", currentProcess->pid);

    if (currentProcess->remaining_time > TIME_QUANTUM) {
        currentProcess->remaining_time -= TIME_QUANTUM;
        printf("Process %d used %d units, remaining time: %d\n", currentProcess->pid, TIME_QUANTUM, currentProcess->remaining_time);
        currentProcess->queue_level = 2;  // Move to Queue 2 (FCFS)
        insertProcess(&queue2, currentProcess);
    } else {
        printf("Process %d completed in Queue 1\n", currentProcess->pid);
        free(currentProcess);  // Process is completed
    }
}

// Function to simulate FCFS scheduling for Queue 2
void scheduleQueue2() {
    if (queue2 == NULL) {
        return;
    }

    ProcessPtr currentProcess = removeProcess(&queue2);
    printf("Queue 2 (FCFS): Running process %d\n", currentProcess->pid);

    printf("Process %d completed with FCFS\n", currentProcess->pid);
    free(currentProcess);  // Process is completed
}

// Function to simulate Shortest Job Next scheduling for Queue 3
void scheduleQueue3() {
    if (queue3 == NULL) {
        return;
    }

    ProcessPtr shortestJob = queue3;
    ProcessPtr prev = NULL, temp = queue3;

    // Find the shortest job in Queue 3
    while (temp->next != NULL) {
        if (temp->next->remaining_time < shortestJob->remaining_time) {
            prev = temp;
            shortestJob = temp->next;
        }
        temp = temp->next;
    }

    if (prev != NULL) {
        prev->next = shortestJob->next;  // Remove shortest job from the list
    } else {
        queue3 = queue3->next;  // Shortest job was the head
    }

    printf("Queue 3 (SJN): Running process %d\n", shortestJob->pid);
    printf("Process %d completed with SJN\n", shortestJob->pid);
    free(shortestJob);  // Process is completed
}

// Function to simulate Multilevel Feedback Queue scheduling
void scheduleMLFQ() {
    printf("\n--- Scheduling Cycle Start ---\n");
    
    // Execute processes in Queue 1 (Round Robin)
    scheduleQueue1();
    
    // Execute processes in Queue 2 (FCFS)
    scheduleQueue2();
    
    // Execute processes in Queue 3 (Shortest Job Next)
    scheduleQueue3();
    
    printf("--- Scheduling Cycle End ---\n\n");
}

int main() {
    // Creating processes and adding them to Queue 1
    insertProcess(&queue1, createProcess(1, 0, 10));
    insertProcess(&queue1, createProcess(2, 0, 5));
    insertProcess(&queue1, createProcess(3, 0, 8));

    // Simulate scheduling cycles
    for (int i = 0; i < 5; i++) {
        scheduleMLFQ();
    }

    return 0;
}
