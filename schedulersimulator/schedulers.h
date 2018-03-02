#pragma once
#include "scheduleralg.h"
#include "types.h"

class FCFS : public SchedulerAlgorithm {
 public:
  FCFS();
  ~FCFS();
  int selectProcess(const std::vector<Process*> *process,
                    const ushort tick,
                    const Process* runningProcess,
                    SchedulerSimulator* ss);
  bool isPreemptive();
};

class RoundRobin : public SchedulerAlgorithm {
 public:
  RoundRobin(ushort quatum);
  ~RoundRobin();
  int selectProcess(const std::vector<Process*> *process,
                    const ushort tick,
                    const Process* runningProcess,
                    SchedulerSimulator* ss);
  bool isPreemptive();
 private:
  ushort quatum;
};

class SPN : public SchedulerAlgorithm {
 public:
  SPN();
  ~SPN();
  int selectProcess(const std::vector<Process*> *process,
                    const ushort tick,
                    const Process* runningProcess,
                    SchedulerSimulator* ss);
  bool isPreemptive();
};

class SRT : public SchedulerAlgorithm {
 public:
  SRT();
  ~SRT();
  int selectProcess(const std::vector<Process*> *process,
                    const ushort tick,
                    const Process* runningProcess,
                    SchedulerSimulator* ss);
  bool isPreemptive();
};

class HRRN : public SchedulerAlgorithm {
 public:
  HRRN();
  ~HRRN();
  int selectProcess(const std::vector<Process*> *process,
                    const ushort tick,
                    const Process* runningProcess,
                    SchedulerSimulator* ss);
  bool isPreemptive();
};

