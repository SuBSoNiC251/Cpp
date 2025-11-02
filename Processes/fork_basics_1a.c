/*My faulty code here*/

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>
// #include <time.h>
// #include <sys/wait.h>
// #include <sys/types.h>

// int main(){
//     pid_t pid = fork();
    
//     if(pid > 0){
//         printf("Parent process running\n");
//         printf("Hello Parent World !!\n");
//         printf("Parent pid : %d\n ---------------------------------- \n", pid);
//     }
    
//     if(pid == 0){
//         printf("Child process\n");
//         execlp("ls","ls","-l",NULL);
//         printf("Child pid : %d\n ---------------------------------- \n", pid);
//     }

//     if(pid < 0){
//         fprintf(stderr,"failed to create a new/child process");
//         printf("Failed pid value : %d\n ---------------------------------- \n", pid);
//     }

//     return 0;
    
// }

/*My corrected code here: */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    fflush(stdout);  // prevent stdout duplication on fork

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process running (PID: %d, PPID: %d)\n", getpid(), getppid());
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");   // runs only if exec fails
        exit(1);
    } 
    else {
        // Parent process
        printf("Parent process running (PID: %d)\n", getpid());
        printf("Child created with PID: %d\n", pid);
        printf("Hello Parent World!!\n");

        wait(NULL);   // wait for child to finish
        printf("Parent: Child finished execution.\n");
    }

    return 0;
}
