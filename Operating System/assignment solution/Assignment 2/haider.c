#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char mess[200];
    int fd;
mkfifo("spipe",0777);

    fd = open("spipe", O_RDONLY);
    if (fd == -1) {
        perror("Error ");
        return 1;
    }

    if (read(fd, mess, sizeof(mess)) == -1) {
        perror("Error");
        close(fd);
        return 1;
    }

    close(fd);
    printf(": %s\n", mess);

    char *ptr = mess;
    while (*ptr) {
        if (islower(*ptr)) {
            *ptr = toupper(*ptr);
        } else if (isupper(*ptr)) {
            *ptr = tolower(*ptr);
        }
        ptr++;
    }

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

    return 0;
}

