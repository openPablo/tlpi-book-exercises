#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int NR_RANDOM_NRS = 6;

int main(int argc, char *argv[]) {
  clock_t start, end;
  char *error_msg = "Usage: ./main <number of files> <dir_path>\n";
  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    printf("%s", error_msg);
    return 1;
  }
  int amount_to_generate = strtol(argv[1], NULL, 10);
  if (amount_to_generate > INT_MAX || amount_to_generate < INT_MIN) {
    printf("%s", error_msg);
    return 1;
  }
  char dest[4096];
  snprintf(dest, sizeof(dest), "%s", argv[1]);
  int i = 0;
  int random_fd, fd;
  char random_buf[8];
  random_fd = open("/dev/urandom", O_RDONLY);
  start = clock();
  for (i = 0; i < amount_to_generate; i++) {
    read(random_fd, random_buf, sizeof(random_buf));
    int random_number = abs(*(int *)random_buf) % (int)pow(10, NR_RANDOM_NRS);
    snprintf(dest, sizeof(dest), "%s/x%d", argv[2], random_number);
    fd = open(dest, O_CREAT | O_WRONLY, 0644);
    write(fd, random_buf, 1);
    close(fd);
  }
  end = clock();
  printf("Time to execute %d files: %f\n", amount_to_generate,
         ((double)(end - start)) / CLOCKS_PER_SEC);
  close(random_fd);
  return 0;
}
