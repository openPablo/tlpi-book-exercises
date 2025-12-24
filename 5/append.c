#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char * argv[]) {
    
    int fd = open(argv[1], O_RDWR | O_APPEND, 660);
    lseek(fd, 0, SEEK_SET);
    write(fd,"test", 4);
    close(fd);
}