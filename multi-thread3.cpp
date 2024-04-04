#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4 // 스레드 개수

// 스레드 함수
void *perform_task(void *args) {
    int *arg = (int *)args;
    int start_num = arg[0];
    int end_num = arg[1];
    int odd_num = arg[2];
    int process_id = arg[3];
    int thread_id = arg[4];

    printf("Process %d, Thread %d: ", process_id, thread_id);
    for (int i = start_num; i <= end_num; ++i) {
        printf("%d ", i * odd_num);
    }
    printf("\n");

    pthread_exit(NULL);
}

// 스레드 생성 함수
void create_threads(int odd_num[], int process_id) {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS][5]; // 스레드에 전달할 인자

    for (int thread_id = 0; thread_id < NUM_THREADS; ++thread_id) { // 프로세스 안에서 스레드 개수만큼 반복
        int start_num = thread_id * (100 / NUM_THREADS) + 1; // 스레드의 시작 숫자
        int end_num = (thread_id + 1) * (100 / NUM_THREADS); // 스레드의 끝 숫자
        thread_args[thread_id][0] = start_num; // 시작 숫자 설정
        thread_args[thread_id][1] = end_num; // 끝 숫자 설정
        thread_args[thread_id][2] = odd_num[process_id]; // 홀수 값 설정
        thread_args[thread_id][3] = process_id + 1; // 프로세스 ID 설정
        thread_args[thread_id][4] = thread_id + 1; // 스레드 ID 설정
        pthread_create(&threads[thread_id], NULL, perform_task, (void *)&thread_args[thread_id]); // 스레드 생성
    }
    
    // 생성된 스레드들 조인
    for (int thread_id = 0; thread_id < NUM_THREADS; ++thread_id) {
        pthread_join(threads[thread_id], NULL);
    }
}

int main() {
    clock_t start, end;
    const int odd_num[] = {3, 5, 7, 9};
    
    start = clock();

    for (int process_id = 0; process_id < NUM_THREADS; ++process_id) { // 스레드 개수만큼 반복
        create_threads(odd_num, process_id);
    }

    end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC; // 시간 측정
    printf("multi process and multi threads elapsed time: %.6f seconds\n", time);

    return 0;
}
