#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string>

const int N = 10;
const int TIMES = 20;

int entra = 0, sale = 0;

struct X {
  int i;
} *buffer;

sem_t empty, full, mutex, scout;

struct ThreadInfo {
  unsigned int id;
  unsigned int times;
  unsigned int bufferSize; 
};

typedef struct ThreadInfo *PThreadInfo;
typedef struct ThreadInfo ThreadInfo;

struct ProdConOpts {
  unsigned int times;
  unsigned int nProds;
  unsigned int nCons;
  int bufferSize;
  bool resumen;
};

typedef struct ProdConOpts ProdConsOpts;
typedef struct ProdConOpts *PProdConsOpts;

void* producer(void*);
void* consumer(void*);
void printRetValInt(const char*, void *);
static void usage(const char*);

int
main(int argc, char *const* argv) {

  ProdConsOpts prodconsopts = { TIMES, 1, 1, N, false };

  int opt;

  while ((opt = getopt(argc, argv, "b:c:p:t:r")) != -1) {
    
    switch(opt) {
    case 'b': {
      std::string soptarg(optarg);
      prodconsopts.bufferSize = std::stoi(soptarg);
      break;
    }

    case 'c': { 
      std::string soptarg(optarg);
      prodconsopts.nCons = std::stoi(soptarg);
      break;
    }

    case 'p': {
      std::string soptarg(optarg);
      prodconsopts.nProds = std::stoi(soptarg);
      break;
    }

    case 't': {
      std::string soptarg(optarg);
      prodconsopts.times = std::stoi(soptarg);
      break;
    }

    case 'r':
      prodconsopts.resumen = true;
      break;

    default:
      usage(argv[0]);
      break;
    }
  }

  if (prodconsopts.resumen) {

    std::cout << "times: " << prodconsopts.times << std::endl
              << "buffer size: " << prodconsopts.bufferSize << std::endl
              << "consumers: " << prodconsopts.nCons << std::endl
              << "producers: " << prodconsopts.nProds << std::endl;
  }    

  buffer = new struct X[prodconsopts.bufferSize];
  
  srand(time(NULL));

  sem_init(&empty, 0, prodconsopts.bufferSize);
  sem_init(&full, 0, 0);
  sem_init(&mutex, 0, 1);
  sem_init(&scout, 0, 1);
  
  pthread_t *prods, *cons;

  prods = new pthread_t[prodconsopts.nProds];
  cons = new pthread_t[prodconsopts.nCons];

  for (unsigned int i = 0; i < prodconsopts.nProds; ++i) {
    PThreadInfo threadInfo = new ThreadInfo;
    threadInfo->id = i;
    threadInfo->times = prodconsopts.times;
    threadInfo->bufferSize = prodconsopts.bufferSize;
  
    pthread_create(&prods[i], NULL, producer, threadInfo);
  }
  
  for (unsigned int i = 0; i < prodconsopts.nCons; ++i) {
    PThreadInfo threadInfo = new ThreadInfo;
    threadInfo = new ThreadInfo;
    threadInfo->id = 1;
    threadInfo->times = prodconsopts.times * prodconsopts.nProds
      / prodconsopts.nCons;
    threadInfo->bufferSize = prodconsopts.bufferSize;
  
    pthread_create(&cons[i], NULL, consumer, threadInfo);
  }

  void *retVal;

  for (unsigned int i = 0; i < prodconsopts.nProds; ++i) {
    pthread_join(prods[i], &retVal);
    printRetValInt("Producer", retVal);
  }

  for (unsigned int i = 0; i < prodconsopts.nCons; ++i) {
    pthread_join(cons[i], &retVal);
    printRetValInt("Consumer", retVal);
  }
  
  sem_destroy(&empty);
  sem_destroy(&full);
  sem_destroy(&mutex);
  sem_destroy(&scout);
  return 0;
}

void*
producer(void *arg) {

  PThreadInfo ti = static_cast<PThreadInfo>(arg);
  
  for (unsigned int i = 0; i < ti->times; ++i) {
    int e = rand();
    
    sem_wait(&scout);
    std::cout << "Producer(" << ti->id
              << ")=" << e << std::endl;
    sem_post(&scout);

    sem_wait(&empty);
    sem_wait(&mutex);
    // Seccion critica
    buffer[entra].i = e;
    entra = (entra + 1) % ti->bufferSize;
    sem_post(&mutex);
    sem_post(&full);

    //sleep(rand() % 4);
  }

  int *pId = new int;
  *pId = ti->id;
  delete ti;

  return pId;
}

void*
consumer(void *arg) {

  PThreadInfo ti = static_cast<PThreadInfo>(arg);
  
  for (unsigned int i = 0;i < ti->times; ++i) {
    
    sem_wait(&full);
    sem_wait(&mutex);
    int e = buffer[sale].i;
    sale = (sale + 1) % ti->bufferSize;
    sem_post(&mutex);
    sem_post(&empty);

    sem_wait(&scout);
    std::cout << "Consumer(" << ti->id << ")=" << e << std::endl;
    sem_post(&scout);
    // sleep(rand() % 4);
  }
  
  int *pId = new int;
  *pId = ti->id;
  delete ti;

  return pId;
}

void printRetValInt(const char*message, void *arg) {

  int *p = (int*) arg;
  std::cout << message << "("
            << *p
            << ")" << " ended" << std::endl;
}

static void
usage(const char* progname) {
  std::cerr << "Usage: " << progname
            << " [-b <bufferSize>] [-c <nCons>] [-p <nProds>] [-t times] [-r]"
            << std::endl;
  ::_exit(1);
}
