#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine(void* arg){
    int seed = rand() % 5;
    printf("%d. Hello thread \n", *(int*) arg);
    sleep(seed);
    printf("Ending thread %d\n", *(int*) arg);
} 

int main(){
    int num[2] = {1,2};
    pthread_t t1, t2;
    // pthread_t t2;
    pthread_create(&t1, NULL, routine, &num[0]);
    pthread_create(&t2, NULL, routine, &num[1]);
    pthread_join(t1, NULL);    
    pthread_join(t2,NULL);
    return 0;
}