#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void calculate(int start, int end, int multiplier, int process_number, int thread_number) {
    printf("Process %d, Thread %d: ", process_number, thread_number);
    for (int i = start; i <= end; ++i) {
        printf("%d ", i * multiplier);
    }
    printf("\n");
}

int main() {
    clock_t start_time = clock();

    const int num_threads = 4;
    const int range = 100;

    const int multipliers[] = {3, 5, 7, 9};

    for (int process_number = 1; process_number <= 4; ++process_number) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork 실패\n");
            return 1;
        } else if (pid == 0) {
            printf("Process %d PID: %d\n", process_number, getpid());

            for (int thread_number = 1; thread_number <= num_threads; ++thread_number) {
                int start = (thread_number - 1) * (range / num_threads) + 1;
                int end = thread_number * (range / num_threads);
                calculate(start, end, multipliers[process_number - 1], process_number, thread_number);
            }
            return 0;
        }
    }

    for (int i = 0; i < 4; ++i) {
        wait(NULL);
    }

    clock_t end_time = clock();
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("전체 계산 시간: %.2f milliseconds\n", duration * 1000);

    return 0;
}
