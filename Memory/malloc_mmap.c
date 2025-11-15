#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("Program break before: %p\n", sbrk(0));

    void *big = malloc(10 * 1024 * 1024);  // 10 MB
    printf("malloc(10MB) pointer:  %p\n", big);
    printf("Program break after:  %p\n", sbrk(0));

    free(big);

    getchar(); // inspect maps

    return 0;
}
