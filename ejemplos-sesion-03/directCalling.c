#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "constantes.h"

int
main() {

  int pid;

  pid = getpid();

  printf("PID: %d\n", pid);

  alarm(CINCO);
  mifuncion(1,2,3);
  pause();

  _exit(CERO);
  return 1;
}
