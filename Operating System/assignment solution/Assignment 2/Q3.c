#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

if(pid<0)
{
        printf("Error\n");
        exit(1);
    
}
    else if (pid == 0) 
    { 
        int start = 0, last = 0;
        close(fd[1]);

        read(fd[0], &start, sizeof(int));

        read(fd[0], &last, sizeof(int));

        close(fd[0]);

        int num = start;
        while (num <= last) {
            if (num > 1) {
                int check = 1;
                for (int i = 2; i*2 <= num; i++) {
                    if (num % i == 0) {
                        check = 0;
                        break;
                    }
                }
                if (check) {
                    printf("%d ", num);
                }
            }
            num++;
        }
        printf("\n");
    } 
    else 
    { 
        int start = 0, last = 0;
        printf("Please enter start value of range: ");
        scanf("%d", &start);
        printf("Please enter end value of range: ");
        scanf("%d", &last);

        close(fd[0]); 
        

        write(fd[1], &start, sizeof(int));
        write(fd[1], &last, sizeof(int));

        close(fd[1]); 
        
    } 

    return 0;
}
