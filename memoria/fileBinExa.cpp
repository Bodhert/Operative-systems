#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int
main(void) {
  char *prog;

  prog = new char[8];

  bcopy("\x0F\x00\x00\x00\xff\xff\xff\xff", prog, 8);

  void *tmp = prog;
  int *p = static_cast<int*>(tmp);

  cout << *p << endl;

  p++;

  cout << *p << endl;

  return EXIT_SUCCESS;
}

  
