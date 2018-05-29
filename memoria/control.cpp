#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

int
main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage control: <shmname>" << endl;
    return 1;
  }
  
  int shm = shm_open(argv[1], O_CREAT | O_RDWR | O_EXCL, 0600);

  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
    return 1;
  }

  off_t size_mem = 1000;

  if (ftruncate(shm, size_mem) == -1) {
    cerr << "Problems with memory size" << endl;
    return 1;
  }

  char *pMem = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE,
                                       MAP_SHARED, shm, 0));

  if ((void *) pMem == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }

  int *pInt = (int *)pMem + 500;

  char c = 'a';
  int number = 0;
  
  for (;;) {

    for (int i = 0; i < 500; ++i) {
      *(pMem + i) = c++;
      c = (c > 'z') ? c = 'a' : c;
    }

    for (int i = 0; i < 125; ++i) {
      *(pInt + i) = number++; 
    }

    sleep(3);
  }

  return 0;
}
