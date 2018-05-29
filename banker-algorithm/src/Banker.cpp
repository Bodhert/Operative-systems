#include "Banker.h"
#include <cstring>
#include <iostream>

Banker::Banker(string filename) :
  inputFile(filename), listProcess(), infoLevel(NoInfo)
{

  ifstream infile(filename.c_str());

  if (!infile)
    throw BankerException(InputException,
			  "opening file");

  infile >> n >> m;

  if (!infile)
    throw BankerException(FormatException,
			  "reading n and m");

  available = new int[m];
  work = new int[m];
  finish = new int[n];
  max = new int*[n];
  allocation = new int*[n];
  need = new int*[n];

  if (!available and !work and !finish and !max and !allocation and !need)
    throw BankerException(MemoryAllocException,
			  "creating vectors and matrix");

  // Reading available
  for (int j = 0; j < m; j++)
     infile >> available[j];

  if (!infile)
    throw BankerException(FormatException,
			  "reading available");

  readMatrix(infile, max, "reading max");

  readMatrix(infile, allocation, "reading allocation");

  // Compute need = max - allocation
  for (int i = 0; i < n; i++) {
    need[i] = new int[m];
    for (int j = 0; j < m; j++)
      need[i][j] = max[i][j] - allocation[i][j];
  }
}

void
Banker::testMemory(void *p) const {
  if (!p)
    throw BankerException(MemoryAllocException,
			  "bad pointer");
}

/* Banker::readMatrix
 * This function read from a in input stream a matrix with n rows
 * and m columns.
 */
void
Banker::readMatrix(ifstream& in, int **matrix, const char* msg) {

  for (int i = 0; i < n; i++) {
    matrix[i] = new int[m];
    testMemory(matrix[i]);

    for (int j = 0; j < m; j++) {
      in >> matrix[i][j];
    }

    if (!in) throw BankerException(FormatException, msg);
  }
}

bool
Banker::isInSafeState() {

  listProcess.erase(listProcess.begin(), listProcess.end());

  for (int j = 0; j < m; j++) work[j] = available[j];
  for (int i = 0; i < n; i++) finish[i] = false;

  int found = 0, preFounded;

  do {
    preFounded = found;

    for (int i = 0; i < n; i++) {
      if (finish[i]) continue;
      if (lessThat(need[i], work, m)) {
	for (int j = 0; j < m; j++) work[j] += allocation[i][j];
	finish[i] = true;
	found++;
	listProcess.push_back(i);
      }
    }
  } while (found < n and found != preFounded);

  return found == n;
}


bool
Banker::isInSafeState2() {

  listProcess.erase(listProcess.begin(), listProcess.end());

  for (int j = 0; j < m; j++) work[j] = available[j];
  for (int i = 0; i < n; i++) finish[i] = false;

  int found = 0, preFounded;

  showMatrices();
  showProcess(-1);
  do {
    preFounded = found;

    for (int i = 0; i < n; i++) {
      if (finish[i]) continue;
      if (lessThat(need[i], work, m)) {
	showProcess(i);
	for (int j = 0; j < m; j++) work[j] += allocation[i][j];
	finish[i] = true;
	found++;
	listProcess.push_back(i);
	showProcess(i);
      }
    }
  } while (found < n and found != preFounded);

  return found == n;
}

void
Banker::showSafeProcesses()
{

  for (vector<int>::iterator it = listProcess.begin();
       it != listProcess.end(); it++) {

    cout << *it << " ";
  }

  cout << endl;
}

bool
Banker::lessThat(const int *x, const int *y, int len) {
  bool ret = false;

  int i = 0;
  for (; i < len and x[i] <= y[i]; i++);

  if (i == len) ret = true;

  return ret;
}

void
Banker::setInfoLevel(InfoLevel infoLevel) {

  this->infoLevel = infoLevel;
}

Banker::BankerException::BankerException(ReasonException r,
					 const char* msg) throw()
  : message(NULL), re(r) {
  const char *reasons[] = { "Input exception ",
			    "Format exception ",
			    "Memory allocation exception: ",
                            NULL };
  int reStrLen = 0;
  for (int i = 0; reasons[i]; i++) {
    int len = ::strlen(reasons[i]);
    if (reStrLen < len) reStrLen = len;
  }

  // Manage to append a new message
  reStrLen += ::strlen(msg);
  message = new char[reStrLen + 2];
  message[0] = '\0';
  ::strcat(::strcat(::strcpy(message, reasons[re]), " "), msg);
}

const char*
Banker::BankerException::what() const throw() {

  return message;
}

Banker::BankerException::~BankerException() throw() {

  if (message)
    delete[] message;
}

template<typename T> void
Banker::showRowN(T* row, int n) {

  for (int i = 0; i < n; i++)
    cout << row[i] << " ";
}

void
Banker::showMatrices() {

  cout << '\t' << "Allocation" << '\t' << "Max" << '\t' << "Need" << '\t' << "Available" << endl;

  for (int i = 0; i < n; i++) {

    cout << i << '\t';
    showRowN(allocation[i], m);
    cout << '\t' << '\t';
    showRowN(max[i], m);
    cout << '\t';
    showRowN(need[i], m);

    if (!i) {
      cout << '\t';
      showRowN(available, m);
    }

    cout << endl;
  }
}

void
Banker::showProcess(int process) {

  cout << "Process: ";

  if (process == -1) cout << ' ';
  else cout << process;

  cout << " finish: ";
  showRowN(finish, n);
  cout << "\twork: ";
  showRowN(work, m);
  cout << endl;
}

int
Banker::getNumberProcess() const {

  return n;
}

int
Banker::getNumberKndResources() const {

  return m;
}

void
Banker::evalRequirement(int* requirement, int nroReq, int nProcess) {

  if (!lessThat(requirement, need[nProcess], m)) {

    cerr << "Process has exhausted resources" << endl;
    return;
  }

  if (!lessThat(requirement, available, m)) {

    cerr << "Process has to wait" << endl;
    return;
  }

  for (int j = 0; j < m; j++) {

    available[j] -= requirement[j];
    allocation[nProcess][j] += requirement[j];
    need[nProcess][j] -= requirement[j];
  }

  if (!isInSafeState2()) {

    cerr << "The requirement could cause a unsafe state" << endl;
    cerr << "rollback the previous requirement" << endl;

    for (int j = 0; j < m; j++) {

      available[j] += requirement[j];
      allocation[nProcess][j] -= requirement[j];
      need[nProcess][j] += requirement[j];
    }
    return;
  }

  showMatrices();
  cerr << "The requirement is possible to give" << endl;
  return;
}
