#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int
main(void) {
  char prog[] = "\x0F\x00\x00\x00\x03\x00\x0F\xC0";

  ofstream fileprog("prog.bew", ios_base::binary);

  fileprog.write(prog, sizeof(prog));
  fileprog.close();

  return EXIT_SUCCESS;
}

  
