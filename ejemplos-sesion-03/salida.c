/*
 * fichero: salida.c
 * 
 * autor: Juan Francisco Cardona McCormick
 *
 */
#include <stdio.h>

int
main(int argc, char *argv[]) {

  fprintf(stdout, "Hola Mundo\n");
  fprintf(stderr, "Adios mundo\n");
  return 0;
}
