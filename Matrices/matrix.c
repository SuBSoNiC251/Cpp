#include <stdio.h>
#include <stdlib.h>
const int size = 3;

int main(int argc,char *argv[]){
    int m = 3, n = 3;
    int arr[size][size];
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < n; j++) {
            arr[i][j] = i + j;
        }
    }
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    printf("arr is : %p\n",arr);
    printf("&arr is : %p\n", &arr);
    printf("&arr is : %p\n", &arr[0]);
    // printf("")
    
    return 0;
}