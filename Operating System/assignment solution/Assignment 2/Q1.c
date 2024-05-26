#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf( "error\n");
        exit(1);
    }
    else if (pid == 0) 
    { 
        printf("\nchild pid: %d\n", getpid());
        printf("\n");
    } else { 
        
        printf(" parent process  display the PID of the child.: %d", pid);
       
    }
    return 0;
}
