#include <stdio.h>

int
main() {
  
  int c;
  while ((c = getc(stdin)) != EOF) {
    c += 7;
    fputc(c, stdout);
  }
  return 0;
}
