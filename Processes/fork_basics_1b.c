#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
    int x = 100;

    pid_t pid = fork();
    
    if(pid < 0){
        perror("Failed to create a new process \n");
        exit(1);
    }
    if(pid > 0){
        printf("Parent process, PID = %d, child PID = %d\n", getpid(), pid);
        x += 20;
        printf("Value of x in Parent is: %d\n",x);
        printf("----------------------- \n");
        wait(NULL);
        printf("Child Execution completed !\n");
    }else{
        printf("Child process, PID = %d, Parent PID = %d\n", getpid(), getppid());
        x += 10;
        printf("Value of x in Child is: %d\n",x);
        printf("----------------------- \n");
    }

    return 0;
}