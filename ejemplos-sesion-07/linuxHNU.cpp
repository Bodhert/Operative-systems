#include <pthread.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

void*
hiloExec(void *arg) {
  int *p = (int *) arg;

  for (int i = 0; i < *p; ++i) {
    cout << "Hola " << i << endl;
  }

  delete p;

  int *ret = new int;

  *ret = 10;

  return (void *) ret;
}

int
main() {
  pthread_t hilo;
  int *p = new int;

  *p = 10000;

  if (pthread_create(&hilo, NULL, hiloExec, (void *)p) != 0) {
    cerr << "Fallo creacion de hilo" << endl;
    exit(0);
  }

  pthread_t hilo2;
  p = new int;

  *p = 20000;

  if (pthread_create(&hilo2, NULL, hiloExec, (void *)p) != 0) {
    cerr << "Fallo creacion de hilo" << endl;
    exit(0);
  }

  int *retValHilo;

  pthread_join(hilo, (void **) &retValHilo);

  cout << "Mi hijo termino con estado " << *retValHilo << endl;

  delete retValHilo;
  
  return 0;
}
