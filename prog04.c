#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/time.h>

#define CHILDREN_COUNT 3

void run_child(int priority) {
    struct sched_param param;
    param.sched_priority = priority;

    if (sched_setscheduler(0, SCHED_FIFO, &param) != 0) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }

    printf("Child process with priority %d is running\n", priority);
    
    // Record start time
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    // Simulate some work
    usleep(1000000);
    
    // Record end time
    gettimeofday(&end, NULL);
    
    // Calculate elapsed time
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    
    printf("Child process with priority %d finished in %.2f seconds\n", priority, elapsed_time);
}

int main() {
    pid_t pid;
    int priorities[CHILDREN_COUNT] = {10, 20, 30}; // Priorities for the child processes

    for (int i = 0; i < CHILDREN_COUNT; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            run_child(priorities[i]);
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process
    // Wait for all child processes to finish
    for (int i = 0; i < CHILDREN_COUNT; ++i) {
        wait(NULL);
    }

    printf("All child processes have finished\n");

    return 0;
}
