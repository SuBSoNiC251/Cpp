// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>

// void* routine(void* arg){
//     int id = *(int*)arg;
//     int seed = rand() % 5;

//     printf("%d. Hello Thread\n",id);
//     sleep(seed);
//     printf("Ending thread %d\n",id);
// }

// int main(){
//     int num[2] = {1,2};
//     pthread_t t1, t2;

//     if(pthread_create(&t1, NULL, routine, &num[0]) != 0){
//         perror("Failed to create the thread 1\n");
//         return 1;
//     }

//     if(pthread_create(&t2, NULL, routine, &num[1]) != 0){
//         perror("Failed to create the thread 2\n");
//         return 2;
//     }

//     if(pthread_join(t1, NULL) != 0){
//         perror("Falied to joing thread 1");
//         return 3;
//     }

//     if(pthread_join(t2, NULL) != 0){
//         perror("Failed to join thread 2");
//         return 4;
//     }

//     return 0;
// }


/*My code is commented out above, below is upgraded ai version*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void* routine(void* arg) {
    int id = *(int*)arg;
    unsigned int seed = time(NULL) ^ id; // thread-safe seed
    int delay = rand_r(&seed) % 5;

    printf("%d. Hello Thread\n", id);
    sleep(delay);
    printf("Ending thread %d (slept %d seconds)\n", id, delay);

    return NULL; // ✅ must return something
}

int main(void) {
    pthread_t t1, t2;
    int num[2] = {1, 2};

    srand(time(NULL)); // seed random once

    if (pthread_create(&t1, NULL, routine, &num[0]) != 0) {
        fprintf(stderr, "Failed to create thread 1\n");
        return 1;
    }

    if (pthread_create(&t2, NULL, routine, &num[1]) != 0) {
        fprintf(stderr, "Failed to create thread 2\n");
        return 2;
    }

    if (pthread_join(t1, NULL) != 0) {
        fprintf(stderr, "Failed to join thread 1\n");
        return 3;
    }

    if (pthread_join(t2, NULL) != 0) {
        fprintf(stderr, "Failed to join thread 2\n");
        return 4;
    }

    printf("Both threads have finished.\n");
    return 0;
}
