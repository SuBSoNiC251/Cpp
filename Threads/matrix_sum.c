#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void create_matrix(int *arr[], int rows, int cols){
    printf("Create Matrix \n");
    arr[rows][cols];
    int num = 0;
    for(int i = 0; i < rows ; i++){
        for(int j = 0 ; i < cols ; j++){
            printf("Enter value (%d,%d): ",i,j);
            scanf("%d",&num);
            arr[i][j] = num;
        }
        printf("\n");
    }
}

void print_matrix(int *arr[]){
    printf("Print Matrix \n");
    printf("Debug value of sizeof(arr): %d\n", arr);
    int size = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0; i < size ; i++){
        for(int j = 0; j < size; j++){
            printf("%d ",arr[i]);
        }
        printf("\n");
    }

    printf("\n\n");
    return;
}

int main(int argc, char *argv[]){
    int rows, cols;
    printf("Enter the number or rows, cols required for the matrices");
    scanf("%d \n %d",&rows,&cols);
    int arr1[rows][cols];
    int arr2[rows][cols];

    create_matrix(&arr1, rows, cols);
    create_matrix(&arr2, rows, cols);

    print_matrix(arr1);
    print_matrix(arr2);
}