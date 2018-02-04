#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
  pid_t hijo;

  fprintf(stdout, "My PID: %d\n", getpid());

  hijo = fork();

  if (hijo == -1) {
    fprintf(stderr, "Error: %d", errno);
    if (errno == EAGAIN) {
      // Error manejo aqui
    }
    exit(0);
  }

  if (hijo == 0) { // El proceso hijo

    fprintf(stdout, "hijo: %d\n", hijo);
    fprintf(stdout, "I have pid: %d\n", getpid());
    fprintf(stdout, "My father is: %d\n", getppid());
    sleep(5);
    return 10;
  }
  else {  // El proceso padre
    int status;
    fprintf(stdout, "My child is: %d\n", hijo);
    kill(hijo, SIGKILL);
    wait(&status);
    if (WIFEXITED(status)) {
      fprintf(stdout, "My child ends with %d\n", 
	      WEXITSTATUS(status));
    }
    else {
      fprintf(stdout, "My child was killed: \n");
    }
  }
  return 0;
}
