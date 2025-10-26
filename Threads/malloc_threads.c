#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void* routine(void *arg) {
    int id = rand() % 5;
    unsigned int seed = time(NULL) ^ id;
    int delay = rand_r(&seed) % 5;

    sleep(delay);
    printf("Current value: %d (waited for %ds)\n",*(int*)arg,delay);
    int* ptr = (int*)malloc(sizeof(int));
    if (!ptr) {
        perror("malloc failed");
        pthread_exit(NULL);
    }

    *ptr = (*(int*)arg) * 2;
    return ptr;   // ✅ return pointer, not value
}

int main(void) {
    srand(time(NULL));

    int num[2] = {10, 20};
    pthread_t t1, t2;
    int *res1, *res2;

    if (pthread_create(&t1, NULL, routine, &num[0]) != 0) {
        fprintf(stderr, "Failed to create thread 1\n");
        return 1;
    }

    if (pthread_create(&t2, NULL, routine, &num[1]) != 0) {
        fprintf(stderr, "Failed to create thread 2\n");
        return 2;
    }

    if (pthread_join(t1, (void**)&res1) != 0) {
        fprintf(stderr, "Failed to join thread 1\n");
        return 3;
    }

    if (pthread_join(t2, (void**)&res2) != 0) {
        fprintf(stderr, "Failed to join thread 2\n");
        return 4;
    }

    printf("Value now (thread 1): %d\n", *res1);
    printf("Value now (thread 2): %d\n", *res2);
    printf("Both threads have finished.\n");

    free(res1);
    free(res2);

    return 0;
}
