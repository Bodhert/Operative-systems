#include "process.h"
#include <iostream>


Process::Process(ushort serviceTime,
                 ushort createdTime,
                 ushort idProcess)
  : serviceTime(serviceTime),
    createdTime(createdTime),
    idProcess(idProcess),
    executionTime(0),
    waitTime(0),
    firstRunTime(-1),
    deathTime(0),
    consumedQuatum(0),
    state(NewState) { }

Process::~Process() { }

void Process::run(ushort tick) {

  if (executionTime < serviceTime) {
    switch (state) {
    case ReadyState:
      state = RunningState;
      if (firstRunTime == -1) firstRunTime = tick;
      break;
    default:
      break;
    }
  }
}

void Process::putReadyState() {

  if (executionTime < serviceTime) {
    state = ReadyState;
  }
}

void Process::tick() {
  if (executionTime < serviceTime) {
    switch (state) {
    case NewState:
      break;
    case ReadyState:
      ++waitTime;
      break;
    case RunningState:
      ++executionTime;
      consumedQuatum--;
      if (executionTime == serviceTime) state = TerminatedState;
      break;
    case TerminatedState:
      break;
    }
  }
  else {
    state = TerminatedState;
  }
}

void Process::preemptive() {
  if (executionTime < serviceTime) {
    switch (state) {
    case RunningState:
      state = ReadyState;
      break;
    default:
      break;
    }
  }
}

void Process::zombie(ushort tick) {
  state = TerminatedState;
  deathTime = tick;
}

bool Process::isEnded() const {
  return state == TerminatedState;
}

ushort Process::getServiceTime() const {
  return serviceTime;
}

ushort Process::getExecutionTime() const {
  return executionTime;
}

ushort Process::getWaitTime() const {
  return waitTime;
}

ushort Process::getCreatedTime() const {
  return createdTime;
}

short Process::getResponseTime() const {
  return firstRunTime;
}

short Process::getReturnTime() const {
  return deathTime - firstRunTime;
}
  
StateProcess Process::getState() const {
  return state;
}

ushort Process::getIdProcess() const {
  return idProcess;
}

ushort Process::getConsumedQuatum() const {
  return consumedQuatum;
}

void Process::setConsumedQuatum(ushort consumedQuatum) {
  this->consumedQuatum = consumedQuatum;
}


void printProcess(ushort tick, const char *message, Process* p) {
  std::cout << message 
            << " Tick(" << tick
            << ") idProcess(" << p->getIdProcess()
            << ") serviceTime(" << p->getServiceTime()
            << ") executionTime(" << p->getExecutionTime()
            << ") state(" << p->getState()
            << ")"
            << std::endl;
}

void printDeathProcess(ushort tick, Process* p) {
  std::cout << "Death process"
            << " Tick(" << tick
            << ") idProcess(" << p->getIdProcess()
            << ") responseTime(" << p->getResponseTime()
            << ") waitTime(" << p->getWaitTime()
            << ") returnTime(" << p->getReturnTime()
            << ")"
            << std::endl;
}
