#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define SIZE_BUFFER 12

int
main() {
  int fd;
  char buffer[SIZE_BUFFER + 1];
  
  bzero(buffer, SIZE_BUFFER);
  
  fd = open("manualCalling.c", O_RDONLY);

  if (fd == -1) {
    fprintf(stderr, "Error abriendo archivo: %d\n", errno);
    _exit(1);
  }

  int tam;
  tam = read(fd, buffer, SIZE_BUFFER);

  if (tam == -1) {
    fprintf(stderr, "Error leyendo archivo: %d\n", errno);
    _exit(2);
  }

  buffer[tam] = '\0';
  while (tam != 0) {
    // fprintf(stdout, "%s", buffer);
    write(1, buffer, tam);
    tam = read(fd, buffer, SIZE_BUFFER);

    if (tam == -1) {
      fprintf(stderr, "Error leyendo archivo: %d\n", errno);
      _exit(3);
    }
    buffer[tam] = '\0';
  }

  close(fd); // Cierra el archivo que se esta leyendo.
  _exit(0); // Termina 
}
