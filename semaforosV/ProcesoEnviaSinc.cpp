/* 
 * fichero: ProcesoEnviaSinc.cpp
 * compilar: $ g++ -o ProcesoEnviaSinc ProcesoEnviaSinc.cpp
 *           $ make ProcesoEnviaSinc
 *
 * proposito: envia una senal para sincronizar un semaforo
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
            << " debido: " << ::strerror(errno)
            << std::endl;
  
  ::exit(1);
}

int
main(int argc, const char* argv[]) {
  
  if (argc != 2) uso(argv[0]);
  
  key_t clave = ::atoi(argv[POS_CLAVE]);
  
  int semId;

  if ((semId = ::semget(clave, 0, 0)) == -1) {
    operSemFallo(argv[0], "obtener id del semaforo", errno);
  }

  /* nroSemaforo, valor, y opciones */
  sembuf opSem = { 0, 1, 0 };

  std::cout << "Envia senal" << std::endl;
  if (::semop(semId, &opSem, 1) == -1) {
    
    operSemFallo(argv[0], "establecer valor semaforo", errno);
  } 
  
  return 0;
}
