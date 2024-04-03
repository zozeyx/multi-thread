#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_THREADS 4
#define NUM_PROCESSES 4

void perform_task(int start, int end, int oddnum, int process_id, int thread_id) {
    printf("Process %d, Thread %d: ", process_id + 1, thread_id + 1);
    for (int i = start_num; i <= end_num; ++i) {
        printf("%d ", i * oddnum);
    }
    printf("\n");
}

int main() {
    int process_id;
    int range = 100;
    clock_t start, end;

    start = clock();

    const int threads = 4;
    const int range = 100;

    const int oddnum[] = {3, 5, 7, 9};

    for (process_id = 0; process_id < NUM_PROCESSES; ++process_id) {
        pid_t pid = fork();
        if (pid == 0) {
            for (int thread_id = 0; thread_id < NUM_THREADS; ++thread_id) {
                int start_num = (thread_id) * (range / NUM_THREADS) + 1;
                int end_num = (thread_id + 1) * (range / NUM_THREADS);
                perform_task(start, end, oddnum[process_id], process_id, thread_id);
            }
        }else if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        } 
        exit(0);
    }

    for (int i = 0; i < 4; ++i) {
        wait(NULL);
    }

    end = clock();
  
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("multi-processes and multi threads elapsed time : %.6f seconds\n", time);

    return 0;
}
