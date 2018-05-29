#include <iostream>
#include <cstdlib>
#include "Banker.h"

using namespace std;

static void
usage(const char* progname) {
  cerr << "Usage: " << progname << " <filename> " << endl;
  ::exit(1);
}

enum ProcReq { EndProcReq, NextProcReq, ReadyProcReq };

ProcReq readingRequirement(const Banker& banker, int& nProcess,
			   int* requirement, const int& nResources) {

  cout << "get process number (<0 to end): ";
  cin >> nProcess;

  if (!cin) {
    cerr << "Bad format" << endl;
    ::exit(1);
  }

  if (nProcess < 0)
    return EndProcReq;

  if (!(nProcess < banker.getNumberProcess())) {
    cerr << "nroProcess incorrect" << endl;
    return NextProcReq;
  }

  cout << "Enter requirement (" << nResources << "): ";

  for (int j = 0; j < nResources; j++) {

    cin >> requirement[j];
  }

  if (!cin) {
    cerr << "Bad format of requirement" << endl;
    return NextProcReq;
  }

  return ReadyProcReq;
}

int
main(int argc, const char *argv[]) {

  if (argc != 2) usage(argv[0]);

  try {

    string filename(argv[1]);
    Banker banker(filename);
    cout << banker.isInSafeState2() << endl;
    banker.showSafeProcesses();

    int nProcess;
    int m = banker.getNumberKndResources();
    int *requirement = new int[m];
    ProcReq procreq;

    while ((procreq = readingRequirement(banker,
					 nProcess,
    					 requirement,
					 m)) != EndProcReq) {

      if (procreq == ReadyProcReq)
	banker.evalRequirement(requirement, m, nProcess);
    }

    delete[] requirement;
  }
  catch (Banker::BankerException &be) {

    cerr << be.what() << endl;
    ::exit(1);
  }

  return 0;
}
