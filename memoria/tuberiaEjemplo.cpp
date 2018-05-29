#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>

int
main(void) {

  int tuberia[2];
  pipe(tuberia);

  pid_t child;
  pid_t child2;

  child = fork();
  
  if (child == 0) { /* child */
    dup2(tuberia[1],1);
    close(tuberia[1]);
    close(tuberia[0]);
    execl("/usr/bin/cat", "cat", "visor.cpp", NULL);
    return  EXIT_FAILURE;
  }
  else {

    child2 = fork();
    if (child2 == 0) {
      dup2(tuberia[0],0);
      close(tuberia[0]);
      close(tuberia[1]);
      execl("/usr/bin/less", "less", NULL);
      return EXIT_FAILURE;
    }
    else {
      close(tuberia[0]);
      close(tuberia[1]);
      int status;
      waitpid(child, &status, 0);
      waitpid(child2, &status, 0);
    }
  }

  return EXIT_SUCCESS;
}
