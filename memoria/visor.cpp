#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>

using namespace std;

int
main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: "<< argv[0] << " <shmname>" << endl;
    return 1;
  }
  
  int shm = shm_open(argv[1], O_RDWR , 0600);

  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
    return 1;
  }

  off_t size_mem = 1000;

  char *pMem = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE,
                                       MAP_SHARED, shm, 0));

  if ((void *) pMem == (void *) -1) { 
    cerr << "Problems with memory map ("
         << errno << ") "
         << strerror(errno)
         << endl;
    return 1;
  }

  int *pInt = (int *)pMem + 500;

  char c = 'a';
  int number = 0;
  
  for (;;) {

    for (int i = 0; i < 3; ++i) {
      cout << "*(pMem + " << i << ")=" << *(pMem + i) << endl;
    }

    for (int i = 0; i < 3; ++i) {
      cout << "*(pInt + " << i << ")=" << *(pInt + i) << endl;
    }

    sleep(5);
  }

  return 0;
}
