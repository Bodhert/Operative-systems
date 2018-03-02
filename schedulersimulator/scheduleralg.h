#pragma once

#include <vector>
#include "process.h"
#include "types.h"

class SchedulerSimulator;

class SchedulerAlgorithm {
 public:
  SchedulerAlgorithm();
  virtual ~SchedulerAlgorithm();
  virtual int selectProcess(const std::vector<Process*> *process,
                            const ushort tick,
                            const Process* runProcess,
                            SchedulerSimulator* ss) = 0;
  virtual bool isPreemptive() = 0;
};
