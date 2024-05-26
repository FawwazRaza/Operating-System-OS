#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int balance1 = 0;
    int balance2 = 0;
    int num = 0;

    int fd[2];
    pipe(fd);
    pid_t childpid = fork();

    if (childpid == -1) {
        printf("Error .\n");
        exit(1);
    } else if (childpid == 0) {
        close(fd[1]); 
        while (1) {
            read(fd[0], &num, sizeof(int));
            if (num == 1) {
                int num1;
                printf("\n1. Withdraw\n2. Deposit : \n");
                scanf("%d", &num1);
                if (num1 == 1) {
                    int num2;
                    printf("\nEnter amount : \n");
                    scanf("%d", &num2);
                    if (num2 >= balance1) {
                        balance1 -= num2;
                        printf("\nBalance is : %d\n", balance1);
                    } else {
                        printf("\nBalance is low.\n");
                    }
                } else if (num1 == 2) {
                    int num2;
                    printf("\nEnter amount : \n");
                    scanf("%d", &num2);
                    balance1 += num2;
                    printf("\nBalance is : %d\n", balance1);
                }
            } else if (num == 2) {
                int num11;
                printf("\n1. Withdraw\n2. Deposit : \n");
                scanf("%d", &num11);
                if (num11 == 1) {
                    int num21;
                    printf("\nEnter amount : \n");
                    scanf("%d", &num21);
                    if (num21 >= balance2) {
                        balance2 -= num21;
                        printf("\nBalance is : %d\n", balance2);
                    } else {
                        printf("\nBalance is low.\n");
                    }
                } else if (num11 == 2) {
                    int num21;
                    printf("\nEnter amount : \n");
                    scanf("%d", &num21);
                    balance2 += num21;
                    printf("\nBalance is : %d\n", balance2);
                }
            }
            close(fd[0]);  
            close(fd[1]);  
        }
        exit(0);  
    } else {
        close(fd[0]);  
        while (1) {
            printf("Please enter account id: \n");
            scanf("%d", &num);
            if (num == 1 || num == 2) {
                write(fd[1], &num, sizeof(int));
            } else {
                printf("Wrong input ----------------exiting.\n");
                break;
            }
        }
        close(fd[1]);  
        waitpid(childpid, NULL, 0);  
    }

    return 0;
}
