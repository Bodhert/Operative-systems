#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int
main() {

  int pid;

  pid = syscall(__NR_getpid);

  printf("PID: %d\n", pid);

  syscall(__NR_alarm,5);
  syscall(__NR_pause);

  syscall(__NR_exit,0);
}
