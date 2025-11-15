#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_uninit;          // .bss
int global_init = 10;       // .data

int main(void) {
    int local = 5;          // stack
    void *heap1 = malloc(1000);
    void *heap2 = malloc(1000);

    printf("Code (text):   %p\n", (void *)main);
    printf("Data (.data):  %p\n", (void *)&global_init);
    printf("BSS  (.bss):   %p\n", (void *)&global_uninit);
    printf("Heap1 malloc:  %p\n", heap1);
    printf("Heap2 malloc:  %p\n", heap2);
    printf("Stack local:   %p\n", (void *)&local);

    printf("\nCheck /proc/%d/maps for full layout\n", getpid());
    getchar(); // pause to inspect
    return 0;
}
