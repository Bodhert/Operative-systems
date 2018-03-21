#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cerrno>
#include <string>
#include <cstring>

int shmid;

const int n = 10;

struct ShareMemory {
  sem_t empty, full, mutex, mutexout;
  int entra = 0, sale = 0;
  struct Buffer {
    int i;
  } buffer[n];
};

typedef struct ShareMemory ShareMemory;
typedef struct ShareMemory* PShareMemory;
PShareMemory shmmem = nullptr;

void productor(unsigned int id, unsigned int times);
void consumidor(unsigned int id, unsigned int times);
void createSharedSemaphore(sem_t*, unsigned int value);
PShareMemory createSharedMemory(void);
void initSeedRandom(unsigned int offset);
void printSemaphoreValue(sem_t& sem);
void checkSemaphoreValues(void);

int
main(int argc, char *const* argv) {

  const char* progname = argv[0];

  std::cout << progname << std::endl;
  
  shmmem = createSharedMemory();
  createSharedSemaphore(&shmmem->empty, n);
  createSharedSemaphore(&shmmem->full, 0);
  createSharedSemaphore(&shmmem->mutex, 1);
  createSharedSemaphore(&shmmem->mutexout, 1);
  
  pid_t firstProductor;
  pid_t secondProductor;  
  pid_t firstConsumer;

  if ((firstProductor = ::fork()) == 0) {
    initSeedRandom(0);
    productor(0, 100);
    _exit(EXIT_SUCCESS);
  }
  
  if ((secondProductor = ::fork()) == 0) {
    initSeedRandom(1);
    productor(1, 200);
    _exit(EXIT_SUCCESS);
  }

  if ((firstConsumer = ::fork()) == 0){ 
    initSeedRandom(2);
    consumidor(0, 300);
    _exit(EXIT_SUCCESS);
  }
  
  int status;
  waitpid(firstProductor, &status, 0);
  waitpid(secondProductor, &status, 0);
  waitpid(firstConsumer, &status, 0);

  sem_destroy(&shmmem->empty);
  sem_destroy(&shmmem->full);
  sem_destroy(&shmmem->mutex);
  sem_destroy(&shmmem->mutexout);

  return 0;
}

void
productor(unsigned int id, unsigned int times) {

  for (unsigned int i = 0; i < times; ++i) {
    int e = rand();
    
    sem_wait(&shmmem->mutexout);
    std::cout << "Producer(" << id
              << ") produced an element: " << e
              << std::endl;
    sem_post(&shmmem->mutexout);

    sem_wait(&shmmem->empty);
    sem_wait(&shmmem->mutex);
    // Seccion critica
    shmmem->buffer[shmmem->entra].i = e;
    shmmem->entra = (shmmem->entra + 1) %n;
    sem_post(&shmmem->mutex);
    sem_post(&shmmem->full);
    // checkSemaphoreValues();
  }
}

void
consumidor(unsigned int id, unsigned int times) {

  for (unsigned int i = 0; i < times; ++i) {

    // checkSemaphoreValues();
    sem_wait(&shmmem->full);
    sem_wait(&shmmem->mutex);
    int e = shmmem->buffer[shmmem->sale].i;
    shmmem->sale = (shmmem->sale + 1) % n;
    sem_post(&shmmem->mutex);
    sem_post(&shmmem->empty);
    sem_wait(&shmmem->mutexout);
    std::cout << "Consumer(" << id
              << ") element received: "
              << e
              << std::endl;
    sem_post(&shmmem->mutexout);
    sleep(rand() % 4);
  }
  
}

void
createSharedSemaphore(sem_t* sem, unsigned int value) {

  if (sem_init(sem, 1, value) < 0) {
    std::cerr << "Cannot create semaphore: "
              << std::strerror(errno)
              << std::endl;
    _exit(EXIT_FAILURE);
  }
}


PShareMemory createSharedMemory(void) {
  
  PShareMemory mem = static_cast<PShareMemory>(mmap(NULL, sizeof(ShareMemory),
                                          PROT_READ | PROT_WRITE,
                                          MAP_SHARED | MAP_ANONYMOUS,
                                          -1, 0));  
  if (shmmem == MAP_FAILED) {
    std::cerr << "Error connecting memory "
              << std::strerror(errno)
              << std::endl;
    _exit(1);
  }

  return mem;
}

void initSeedRandom(unsigned int offset) {
  srand(time(nullptr) + offset);
}

void printSemaphoreValue(const char *message, sem_t *sem) {
  int svalue;

  ::sem_getvalue(sem, &svalue);
  
  std::cout << "sem(" << message << ")=" << svalue << std::endl; 
}

void checkSemaphoreValues(void) {

  printSemaphoreValue("full", &shmmem->full);
  printSemaphoreValue("empty", &shmmem->empty);
  printSemaphoreValue("mutex", &shmmem->mutex);
  printSemaphoreValue("mutexout", &shmmem->mutexout);
}
