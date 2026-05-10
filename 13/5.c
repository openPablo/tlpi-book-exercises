// Implement tail -n <nr> <file>
// Get <nr> last lines from <file>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int step_size = 10;
  int fd, i, filesize, MAX_LINES, cur_offset = 0, linecount = 0;
  char buf[step_size];
  ssize_t nbytes;
  int total_offset = -step_size;

  if (argc != 3 || (strcmp(argv[1], "--help") == 0)) {
    printf("Usage: %s <nr_of_lines> <file_path>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if ((fd = open(argv[2], O_RDONLY)) == -1) {
    printf("Failed opening %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }
  MAX_LINES = atoi(argv[1]);
  filesize = lseek(fd, 0, SEEK_END);
  lseek(fd, total_offset, SEEK_END);

  while ((linecount < MAX_LINES) && total_offset < filesize) {
    read(fd, buf, step_size);
    for (int i = step_size - 1; i >= 0; i--) {
      if (buf[i] == '\n') {
        linecount++;
        if (linecount == 11) {
          break;
        }
      }
      cur_offset--;
    }
    total_offset -= step_size;
    if (abs(total_offset) > filesize) {
      total_offset = filesize;
    }
    lseek(fd, total_offset, SEEK_END);
  }
  lseek(fd, cur_offset, SEEK_END);

  while ((nbytes = read(fd, buf, step_size)) > 0) {
    write(STDOUT_FILENO, buf, nbytes);
  }
  exit(EXIT_SUCCESS);
}
