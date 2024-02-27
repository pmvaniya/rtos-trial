#include <sched.h>
#include <stdio.h>

int main() {
    struct sched_param param;
    param.sched_priority = 10; // Set priority (0-99, with 99 being highest)

    if (sched_setscheduler(0, SCHED_FIFO, &param) != 0) {
        perror("sched_setscheduler");
        return 1;
    }

    printf("Program with increased priority\n");
    return 0;
}
