#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char mess[100];
    mkfifo("npipe", 0777); 
    int fd;

    fd = open("npipe", O_RDONLY);
    if (fd == -1) {
        perror("Error ");
        return 1;
    }

    if (read(fd, mess, sizeof(mess) ) == -1) {
        perror("Error ");
        close(fd);
        return 1;
    }

    close(fd);
    char opt;
    int oprd1, oprd2;

    sscanf(mess, "%c %d %d", &opt, &oprd1, &oprd2);

    int total;
    switch (opt) {
        case '+':
            {total = oprd1 + oprd2;
            break;}
        case '-':
            {total = oprd1 - oprd2;
            break;}
        case '*':
        {    total = oprd1 * oprd2;
            break;
        }
        case '/':
        {
            if (oprd2 == 0) {
                printf("Error: div zero!\n");
                return 1;
            }
            total = oprd1 / oprd2;
            break;
            
        }
        default:
            {printf("error inv\n");
            return 1;}
    }

//    printf("total is  : %d \n", total);
fd=open("npipe",O_WRONLY);
 if (fd == -1) {
        perror("Error ");
        return 1;
    }

    if (write(fd, &total, sizeof(total)) == -1) {
        perror("Error ");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

