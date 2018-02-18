#include <windows.h>
#include <iostream>

using namespace std;

int k = 0;

DWORD WINAPI hiloExec(LPVOID arg) {
  int *p = (int *) arg;

  for (int i = 0; i < *p; ++i) {
    cout << "Hola: " << i << " k: " << k << endl;
    k++;
  }

  return 11;
}

int
main(void) {

  HANDLE hHilo;
  DWORD dwThreadId;

  int *pVeces = new int;

  hHilo = CreateThread(NULL,     // lpThreadAttributes
                       0,        // dwStackSize
                       hiloExec, // lpStartAddres
                       pVeces,   // lpParameter 
                       0,        // dwCreationFlags
                       &dwThreadId // lpThreadId
                       );

  if (hHilo == NULL) {
    cerr << "Error creando hilo: " << GetLastError << endl;
    ExitProcess(1);
  }

  for (int j = 0; j < 1000; ++j) {
     cout << "Otro hilo: " << k << endl;
     k += 4;
   }
  
   DWORD status;

   cerr << "Hilo: " << dwThreadId << endl;

   status = WaitForSingleObject(hHilo, 0);

   cout << "Hilo termino con estado: " << status;

   ExitProcess(0);
   return 0;
}
