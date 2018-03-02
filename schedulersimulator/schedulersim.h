#pragma once

#include <vector>
#include "types.h"
#include "process.h"
#include "scheduleralg.h"

class SchedulerSimulator {
 public:
  SchedulerSimulator(std::vector<Process*> newProcess,
                     SchedulerAlgorithm *schalg);
  SchedulerSimulator(std::vector<Process*> newProcess,
                     std::vector<SchedulerAlgorithm*> feedBackAlgorithms);
  ~SchedulerSimulator();
  void start();
  void makeTick();
  ushort getCurrentTime() const;
  bool isDone() const;
  void activateProcess(int nQueue, int nextProcessRunnning);
 private:
  std::vector< std::vector<Process*> > feedBackProcess;
  std::vector<Process*> newProcess;
  std::vector<Process*> readyProcess;
  std::vector<Process*> terminatedProcess;
  Process*           runningProcess;
  ushort             tick;
  SchedulerAlgorithm *schalg;
  ushort             nProcess;
  void admit();
};
