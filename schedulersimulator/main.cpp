#include "schedulersim.h"
#include "schedulers.h"
#include <iostream>
#include <vector>

int
main(int argc, char * const argv[]) {

  int idPro = 0, ct, st;
  std::vector<Process*> newProcess;

  while (std::cin >> ct >> st) {
    newProcess.push_back(new Process(st, ct, idPro++));
  }

  SchedulerAlgorithm *sa = new HRRN();
  // new SPN();
  // new RoundRobin(4);
  // new RoundRobin(1);
  // new FCFS();
  SchedulerSimulator ss(newProcess, sa);

  ss.start();
  while (ss.isDone()) {
    ss.makeTick();
  }

  delete sa;

  return 0;
}
