#include "schedulersim.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>

SchedulerSimulator::SchedulerSimulator(std::vector<Process*> newProcess,
                                       SchedulerAlgorithm *schalg) :
  feedBackProcess(),
  newProcess(newProcess),
  readyProcess(),
  terminatedProcess(),
  runningProcess(0),
  tick(0),
  schalg(schalg)
{
  nProcess = newProcess.size();
}

SchedulerSimulator::SchedulerSimulator(std::vector<Process*> newProcess,
                                       std::vector<SchedulerAlgorithm*> feedBackAlgorithms) :
  
  feedBackProcess(),
  newProcess(newProcess),
  readyProcess(),
  terminatedProcess(),
  runningProcess(0),
  tick(0),
  schalg()
{
  nProcess = newProcess.size();
}

SchedulerSimulator::~SchedulerSimulator() { }

void SchedulerSimulator::admit() {
  newProcess.erase(std::remove_if(newProcess.begin(),
                                  newProcess.end(),
                                  [this](Process *p)
                                  {
                                    if (p->getCreatedTime() == this->tick) {
                                      printProcess(tick, "New Process", p);
                                      p->putReadyState();
                                      this->readyProcess.push_back(p);
                                      return true;
                                    }
                                    else {
                                      return false;
                                    }
                                  }),
                                  newProcess.end());
}

void SchedulerSimulator::start() {

  admit();
  
  activateProcess(0,
                  schalg->selectProcess(&readyProcess,
                                        tick,
                                        runningProcess,
                                        this));
}

void SchedulerSimulator::makeTick() {
  tick++;
  
  admit();
  
  for (auto p : newProcess) p->tick();
  
  for (auto p : readyProcess) p->tick();
 
  runningProcess->tick();

  if (runningProcess->isEnded()) {
    
    terminatedProcess.push_back(runningProcess);
    runningProcess->zombie(tick);
    printDeathProcess(tick, runningProcess);
    runningProcess = nullptr;
  }
     
  if (schalg->isPreemptive()) {
    
    activateProcess(0,
                    schalg->selectProcess(&readyProcess,
                                          tick,
                                          runningProcess,
                                          this));
  }
  else {
    if (!runningProcess) {
      activateProcess(0,
                      schalg->selectProcess(&readyProcess,
                                            tick,
                                            runningProcess,
                                            this));
    }
  }
}

bool SchedulerSimulator::isDone() const {
  
  return terminatedProcess.size() != nProcess;
}

void SchedulerSimulator::activateProcess(int nQueue,
                                         int nextProcessRunning) {
  if (nextProcessRunning >= 0) {
    if (runningProcess) {
      runningProcess->putReadyState();
      printProcess(tick, "Ready process", runningProcess);
      readyProcess.push_back(runningProcess);
    }
    runningProcess = readyProcess[nextProcessRunning];
    printProcess(tick, "Running Process", runningProcess);
    readyProcess.erase(readyProcess.begin() + nextProcessRunning);
    runningProcess->run(tick);
  }
}
