#pragma once

#include "types.h"

class Process {
public:
  Process(ushort serviceTime,
          ushort createTime,
          ushort idProcess);
  ~Process();
  void run(ushort tick);
  void putReadyState();
  void preemptive();
  void tick();
  void zombie(ushort tick);
  bool isEnded() const;
  ushort getServiceTime() const;
  ushort getExecutionTime() const;
  ushort getWaitTime() const;
  ushort getCreatedTime() const;
  ushort getIdProcess() const;
  short  getResponseTime() const;
  short  getReturnTime() const;
  ushort getConsumedQuatum() const;
  void   setConsumedQuatum(ushort consumedQuatum); 
  StateProcess getState() const;
private:
  ushort serviceTime;
  ushort createdTime;
  ushort idProcess;
  ushort executionTime;
  ushort waitTime;
  short  firstRunTime;
  short  deathTime;
  ushort consumedQuatum;
  StateProcess state;
};


void printProcess(ushort tick, const char* message, Process *p);
void printDeathProcess(ushort tick, Process *p);
