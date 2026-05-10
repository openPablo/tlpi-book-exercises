#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#ifndef BUF_SIZE /* Allow "cc -D" to override definition */
#define BUF_SIZE 4096
#endif

int main(int argc, char *argv[]) {
  int inputFd, outputFd, openFlags;
  mode_t filePerms;
  ssize_t numRead;
  char buf[BUF_SIZE];
  clock_t start, end;

  if (argc != 3 || strcmp(argv[1], "--help") == 0)
    printf("%s old-file new-file\n", argv[0]);

  inputFd = open(argv[1], O_RDONLY);
  if (inputFd == -1)
    printf("opening file %s", argv[1]);

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | O_SYNC | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |
              S_IWOTH; /* rw-rw-rw- */
  outputFd = open(argv[2], openFlags, filePerms);
  if (outputFd == -1)
    printf("opening file %s", argv[2]);

  start = clock();
  while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
    if (write(outputFd, buf, numRead) != numRead)
      printf("write() returned error or partial write occurred");
  if (numRead == -1)
    printf("read");
  if (close(inputFd) == -1)
    printf("close input");
  if (close(outputFd) == -1)
    printf("close output");
  end = clock();
  printf("time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
  exit(EXIT_SUCCESS);
}
