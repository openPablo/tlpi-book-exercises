#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdio.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif


int main (int argc, char * argv[]){
    char buffer[BUF_SIZE];
    ssize_t numRead;
    int fdSrc = open(argv[1], O_RDONLY);
    if (argc != 3 || ) {

    }
    if (fdSrc == -1) {
        perror("opening input file");
        exit(EXIT_FAILURE);
    }
    int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int fdTarget = open(argv[2], openFlags, filePerms);
    if (fdTarget == -1){
        perror("opening output file");
        exit(EXIT_FAILURE);
    }
        
    while((numRead = read(fdSrc, buffer, BUF_SIZE)) > 0){
        if(numRead != write(fdTarget, buffer, numRead)) {
            perror("Wasn't able to write whole buffer");
            exit(EXIT_FAILURE);
        }
    }
    if (numRead == -1) {
        perror("Wasn't able to read file");
        exit(EXIT_FAILURE);
    }
    close(fdSrc);
    close(fdTarget);
    exit(EXIT_SUCCESS);
}

