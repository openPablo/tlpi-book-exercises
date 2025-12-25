#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    if (argc < 3){
        errno = EINVAL;
        perror("atomic_append filename num-bytes [x]");
        return 1;
    }
    int flags = O_CREAT | O_WRONLY | O_APPEND;
    bool no_append = (argc > 3 && strcmp(argv[3], "x") == 0); 
    if (no_append){
        flags &= ~(O_APPEND);
    }
    int fd = open(argv[1], flags, 0600);
    int byteCounter = atoll(argv[2]);
    while(byteCounter > 0){
        if(no_append){
            lseek(fd, 0, SEEK_END);
        }
        int res = write(fd,"x", 1);
        if (res == -1) {
            errno = EIO;
            perror("Error writing to file");
            close(fd);
            return 1;
        }
        byteCounter -= 1;
    }
    close(fd);
    return 0;
}