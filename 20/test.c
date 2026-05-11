#include "abort.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ignore_abrt() { printf("hehe... ignore abort! xD\n"); }
int main() {
  int i;
  signal(SIGABRT, ignore_abrt);
  for (i = 0; i < 10; i++) {
    printf("Sleeping...\n");
    if (i > 3) {
      abort_pablo();
    }
    sleep(1);
  }
}
