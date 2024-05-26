#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char mess[] = "What's Up";
    mkfifo("spipe", 0777); 
    int fd;

    fd = open("spipe", O_WRONLY);
    if (fd == -1) {
        perror("Error ");
        return 1;
    }

    if (write(fd, mess, strlen(mess) + 1) == -1) {
        perror("Error ");
        close(fd);
        return 1;
    }

    close(fd);
    char messs[200];
fd=open("spipe",O_RDONLY);
 if (fd == -1) {
        perror("Error ");
        return 1;
    }

    if (read(fd, messs, sizeof(messs)) == -1) {
        perror("Error ");
        close(fd);
        return 1;
    }
    printf("%s\n",messs);
    close(fd);
    return 0;
}

