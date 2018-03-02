#include "schedulers.h"
#include "schedulersim.h"
#include <iostream>
#include <limits>

FCFS::FCFS() : SchedulerAlgorithm() {}

FCFS::~FCFS() { }

int
FCFS::selectProcess(const std::vector<Process*> *process,
                    const ushort,
                    const Process*,
                    SchedulerSimulator* ss) {
  if (process->size() > 0) return 0;
  return -1;
}

bool
FCFS::isPreemptive() {
  
  return false;
}

RoundRobin::RoundRobin(ushort quatum) :
  SchedulerAlgorithm(), 
  quatum(quatum) { }

RoundRobin::~RoundRobin() { }

int
RoundRobin::selectProcess(const std::vector<Process*> *process,
                          const ushort tick,
                          const Process* runningProcess,
                          SchedulerSimulator* ss) {

  if (!runningProcess) {
    if (process->size() > 0) {
      (*process)[0]->setConsumedQuatum(quatum);
      return 0;
    }
  }
  else {
    if (runningProcess->getConsumedQuatum() == 0) {
      if (process->size() > 0) {
        (*process)[0]->setConsumedQuatum(quatum);
        return 0;
      }
    }
  }
  return -1;
}

bool
RoundRobin::isPreemptive() {
  
  return true;
}

SPN::SPN() : 
  SchedulerAlgorithm() { }

SPN::~SPN() { }

int
SPN::selectProcess(const std::vector<Process*> *process,
                   const ushort tick,
                   const Process* runningProcess,
                   SchedulerSimulator* ss) {
  ushort min = std::numeric_limits<unsigned short>::max();
  ushort i = 0;
  int retValue = -1;
  for (; i < process->size(); ++i) {
    if ((*process)[i]->getServiceTime() < min) {
      retValue = i;
      min = (*process)[i]->getServiceTime();
    }
  }
  
  return retValue;
}

bool
SPN::isPreemptive() {
  
  return false;
}

SRT::SRT() : 
  SchedulerAlgorithm() { }

SRT::~SRT() { }

int
SRT::selectProcess(const std::vector<Process*> *process,
                   const ushort tick,
                   const Process* runningProcess,
                   SchedulerSimulator* ss) {
  ushort min = std::numeric_limits<unsigned short>::max();
  ushort i = 0;
  int retValue = -1;
  for (; i < process->size(); ++i) {
    ushort tmp = (*process)[i]->getServiceTime() - (*process)[i]->getWaitTime();
    if (tmp < min) {
      retValue = i;
      min = tmp;
    }
  }
  
  return retValue;
}

bool
SRT::isPreemptive() {
  
  return true;
}

HRRN::HRRN() : 
  SchedulerAlgorithm() { }

HRRN::~HRRN() { }

int
HRRN::selectProcess(const std::vector<Process*> *process,
                   const ushort tick,
                   const Process* runningProcess,
                   SchedulerSimulator* ss) {
  double max = 0.0d;
  ushort i = 0;
  int retValue = -1;
  for (; i < process->size(); ++i) {
    double tmp = ((double) (*process)[i]->getServiceTime() + (double) (*process)[i]->getWaitTime())
      / (double) (*process)[i]->getWaitTime();
    std::cout << "tmp(" << tmp << ")" << " max(" << max << ")" << std::endl;
    if (max < tmp) {
      retValue = i;
      max = tmp;
    }
  }
  
  return retValue;
}

bool
HRRN::isPreemptive() {
  
  return false;
}
