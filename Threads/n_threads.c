#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void shuffle(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void* routine(void *arg){
    int id = rand() % 5;
    unsigned int seed = time(NULL) ^ id;
    int delay = rand_r(&seed) % 5;
    sleep(delay);
    int num = *(int*)arg;
    printf("Hello World %d\n",num);
    return NULL;
}

int main(int argc, char* argv[]){

    // int m = 1000;
    // int arr[m];
    // for (int i = 0; i < m; i++)
    //     arr[i] = i + 1;  // fill 1–1000

    // srand(time(NULL));
    // shuffle(arr, m);

    // for (int i = 0; i < m; i++)  // print first 100 as example
    //     printf("%d, ", arr[i]);
    // printf("\n");

    /*thread section starts from here*/
    int n = 0;
    printf("Enter the number of threads you want run: ");
    scanf("%d",&n);

    int ids[n];
    pthread_t threads[n];

    for(int i = 0; i < n ; i++){
        ids[i] = i+1;
        if(pthread_create(&threads[i], NULL, routine, &ids[i]) != 0){
            fprintf(stderr, "Failed to create thread %d\n", ids[i]);
            return ids[i];
        }
    }

    for(int i = 0; i < n ; i++){
        if(pthread_join(threads[i], NULL) != 0){
            fprintf(stderr, "Falied to join thread %d\n", i+1);
            return i+1;
        }
    }

    printf("Finished running all threads\n");

    return 0;
}