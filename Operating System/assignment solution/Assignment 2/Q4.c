#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
    int fd1[2]; 
    int fd2[2]; 

    pipe(fd1);
    pipe(fd2);

    pid_t pid = fork();

    if(pid < 0) {
        printf( "error\n");
        exit(1);
    } 
    else if (pid == 0) {
        close(fd1[1]); 
        close(fd2[0]); 

        int size;
        read(fd1[0], &size, sizeof(int));

        int arr[size];
        read(fd1[0], arr, sizeof(int) * size);

        close(fd1[0]); 

        int sum = 0;
       int i = 0; 
        while (i < size) {
            sum += arr[i];
            i++;
        }
        write(fd2[1], &sum, sizeof(int));
        close(fd2[1]); 
    } else { 
        close(fd1[0]); 
        close(fd2[1]); 

        int arr[] = {6,8,2,0,4};
        int size = sizeof(arr) / sizeof(arr[0]);

        write(fd1[1], &size, sizeof(int));
        write(fd1[1], arr, sizeof(int) * size);

        close(fd1[1]); 

        int sum;
        read(fd2[0], &sum, sizeof(int));

        close(fd2[0]); 

        printf(" sum is: %d", sum);
    }

    return 0;
}
