#include <iostream>
#include <sched.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int k = 0;

int
hiloExec(void *arg) {
  int *p = (int *) arg;

  for (int i = 0; i < *p; ++i) {
    cout << "Hola: " << i << " k: " << k <<  endl;
    k++;
  }

  return 11;
}

int
main() {

   char *stackHilo;

   stackHilo = new char[1024];

   pid_t hilo;

   int *pVeces = new int;

   *pVeces = 1000;

   hilo = clone(hiloExec, stackHilo + 1024,
               CLONE_FILES | CLONE_FS | CLONE_IO | CLONE_PARENT 
                | CLONE_SIGHAND | CLONE_VM, pVeces, NULL, NULL);
   

   if (hilo < 0) {
      cerr << "Error creando hilo: " << hilo << endl;
      exit(1);
   }


   for (int j = 0; j < 1000; ++j) {
     cout << "Otro hilo: " << k << endl;
     k += 4;
   }

   int status;

   cerr << "Hilo: " << hilo << endl;

   waitpid(hilo, &status, 0);

   cout << "Hilo termino con estado: " << status;

   return 0;
}
