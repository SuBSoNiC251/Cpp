#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    void *start = sbrk(0);
    printf("%p\n", (void*)start);
    printf("%p\n",(void *)&start);
    printf("Initial program break: %p\n\n", start);


    printf("%ld\n", (long*)start);
    printf("%ld\n", (long*)&start);
    printf("Initial program break: %ld\n\n",(long*)start);


    void *a = malloc(1000);
    printf("After malloc(1000):    %p\n", sbrk(0));
    printf("After malloc(1000):    %ld\n\n",(long*) sbrk(0));

    void *b = malloc(10000);

    printf("After malloc(10000):   %p\n", sbrk(0));
    printf("After malloc(10000):   %ld\n", (long*)sbrk(0));


    free(a); free(b);

    getchar();
    return 0;
}