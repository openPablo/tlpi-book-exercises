#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int maxLen = 1024;
    char *buffer = malloc(maxLen);
    if (buffer == NULL) {
        perror("malloc");
        exit(1);
    }


    ssize_t readNum = read(STDIN_FILENO, buffer, maxLen);
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    write(fd,buffer,readNum);
    exit(0);
}

