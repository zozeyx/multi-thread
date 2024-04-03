#include <stdio.h>
#include <time.h>

void perform_task(int start_num, int end_num, int odd_num) {
    for (int i = start_num; i <= end_num; ++i) {
        printf("%d ", i * odd_num);
    }
    printf("\n");
}

int main() {
    clock_t start, end;
    const int range = 100;
    const int odd_num[] = {3, 5, 7, 9};

    start = clock();

    for (int i = 0; i < 4; ++i) {
        perform_task(1, range, odd_num[i]);
    }

    end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Single process and single thread elapsed time: %.6f seconds\n", time);

    return 0;
}
