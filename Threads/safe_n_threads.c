#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

void* routine(void *arg) {
    int id = *(int*)arg;                         // use the ID passed from main

    // Per-thread RNG seed (thread-safe with rand_r)
    unsigned int seed = (unsigned)time(NULL) ^ (unsigned)pthread_self() ^ (unsigned)id;
    int delay = rand_r(&seed) % 5;               // 0..4 seconds

    printf("[Thread %d] Sleeping for %ds...\n", id, delay);
    sleep(delay);

    int *result = malloc(sizeof *result);
    if (!result) {
        perror("malloc");
        pthread_exit(NULL);
    }
    *result = id * id;
    printf("[Thread %d] Done. Result = %d\n", id, *result);

    pthread_exit(result);                         // return heap pointer
}

int main(void) {
    int N;
    printf("Enter number of threads: ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        fprintf(stderr, "Invalid N\n");
        return 1;
    }

    // Allocate arrays dynamically (safer than VLAs for large N)
    pthread_t *threads = malloc((size_t)N * sizeof *threads);
    int       *ids     = malloc((size_t)N * sizeof *ids);
    int      **results = malloc((size_t)N * sizeof *results);
    if (!threads || !ids || !results) {
        fprintf(stderr, "Allocation failed\n");
        free(threads); free(ids); free(results);
        return 1;
    }

    // Create threads
    for (int i = 0; i < N; i++) {
        ids[i] = i + 1; // IDs: 1..N
        if (pthread_create(&threads[i], NULL, routine, &ids[i]) != 0) {
            perror("pthread_create");
            // Join any already-started threads before exit
            for (int k = 0; k < i; k++) pthread_join(threads[k], (void**)&results[k]);
            free(threads); free(ids); free(results);
            return 1;
        }
    }

    // Join threads and collect results
    for (int i = 0; i < N; i++) {
        void *ret = NULL;
        if (pthread_join(threads[i], &ret) != 0) {
            perror("pthread_join");
            ret = NULL;
        }
        results[i] = (int*)ret; // may be NULL on failure
    }

    puts("All threads finished!\nResults:");
    for (int i = 0; i < N; i++) {
        if (results[i]) {
            printf("Thread %d: %d\n", i + 1, *results[i]);
            free(results[i]); // free per-thread heap
        } else {
            printf("Thread %d: (no result)\n", i + 1);
        }
    }

    free(threads);
    free(ids);
    free(results);
    return 0;
}
