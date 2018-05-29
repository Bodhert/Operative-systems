#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int
main(int argc, char *argv[]) {

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <memname> " << endl;
    return 1;
  }

  if (shm_unlink(argv[1]) == -1) {
    cerr << "Cannot erased" << endl;
    return 1;
  }

  return EXIT_SUCCESS;
}
