#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
    int fd = open("hostss.txt",O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
}