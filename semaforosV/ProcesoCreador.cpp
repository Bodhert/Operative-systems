/* 
 * fichero: ProcesoCreador.cpp
 * compilar: $ g++ -o ProcesoCreador ProcesoCreador.cpp
 *           $ make ProcesoCreador
 *
 * proposito: Crear un semaforo tipo System V
 */
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

const unsigned POS_CLAVE = 1;
const unsigned POS_VALOR_INICIAL = 2;
const unsigned VALOR_INICIAL_DEFAULT = 0;

static void
uso(const char* programa) {

  std::cerr << "Uso: " 
       << programa 
            << " clave [valinit = 0] " << std::endl;

  exit(1);
}

static void
operSemFallo(const char* programa, const char* mensaje,
	     int nroError) {

  std::cerr << "Programa: "  << programa
            << " " << mensaje
            << " errorno: " << nroError
            << " debido: " << ::strerror(errno)
            << std::endl;
  exit(1);
}

int
main(int argc, const char* argv[]) {
  
  if (argc < 2 or argc > 3) uso(argv[0]);
  
  int valInicial = argc == 3 ? ::atoi(argv[POS_VALOR_INICIAL])
    : VALOR_INICIAL_DEFAULT;
  key_t clave = ::atoi(argv[POS_CLAVE]);
  
  int semId;

  if ((semId = ::semget(clave, 1,
                        IPC_CREAT | IPC_EXCL | 0660 )) == -1) {
    operSemFallo(argv[0], "creacion de semaforo", errno);
  }

  std::cout << "Semaforo identificador: " << semId << std::endl;
  
  if (::semctl(semId, 0, SETVAL, valInicial) == -1) {
    
    operSemFallo(argv[0], "establecer valor semaforo", errno);
  } 
  
  return 0;
}
