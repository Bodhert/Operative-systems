#include <stdio.h>

int
main(int argc, char *argv[], char* env[]) {
  int n = 0;

  while (n < argc) {
    printf("%d %s\n", n, argv[n]);
    n++;
  }
  
  n = 0;
  while (env[n]) {
    printf("%d %s\n", n, env[n]);
    n++;
  }
  return 0;
}
