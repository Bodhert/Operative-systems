/* 
 * fichero: ProcesoEsperaSinc.cpp
 * compilar: $ g++ -o ProcesoEsperaSinc ProcesoEsperaSinc.cpp
 *           $ make ProcesoEsperaSinc
 *
 * proposito: Espera un evento en un semaforo 
 */
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

const unsigned POS_CLAVE = 1;

static void
uso(const char* programa) {

  std::cerr << "Uso: " 
            << programa 
            << " clave " << std::endl;

  ::exit(1);
}

static void
operSemFallo(const char* programa, const char* mensaje,
	     int nroError) {

  std::cerr << "Programa: "  << programa
            << " " << mensaje
            << " errorno: " << nroError
            << " debido: " << std::strerror(errno)
            << std::endl;
  ::exit(1);
}

int
main(int argc, const char* argv[]) {
  
  if (argc != 2) uso(argv[0]);
  
  key_t clave = atoi(argv[POS_CLAVE]);
  
  int semId;

  if ((semId = ::semget(clave, 0, 0)) == -1) {
    operSemFallo(argv[0], "obtener id del semaforo", errno);
  }

  /* nroSemaforo, valor, y opciones */
  sembuf opSem = { 0, -1, 0 };

  std::cout << "Inicia espera" << std::endl;
  
  if (::semop(semId, &opSem, 1) == -1) {
    
    operSemFallo(argv[0], "establecer valor semaforo", errno);
  }

  std::cout << "Senal recibida" << std::endl;
  
  return 0;
}
