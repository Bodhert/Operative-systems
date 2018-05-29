#pragma once
#include <string>
#include <fstream>
#include <exception>
#include <vector>

using namespace std;

class Banker {
 public:
  enum ReasonException { InputException, // Problems while open and read file
			 FormatException, // The input file is not well
			 // formed
			 MemoryAllocException // Problems with memory
  };
  enum InfoLevel { NoInfo,
		   InfoLevel1,
		   InfoLevel2,
		   InfoLevel3 };
 private:
  int *available;   // A vector(m) of available resources
  int **max;        // A max(n,m) the max demand fo each process
  int **allocation; // A allocation(n,m) the number of resources allocated
  int **need;       // max(n,m) - allocation(n,m)
  int *work;
  int *finish;
  int n; // Number of process
  int m; // Number of resources
  string inputFile;
  vector<int> listProcess;
  inline void testMemory(void* p) const;
  inline void readMatrix(ifstream& in, int **matrix, const char* msg);
  inline bool lessThat(const int *x, const int *y, int n);
  template<typename T> void showRowN(T* row, int n);
  void showProcess(int process);
  void showMatrices();
  InfoLevel infoLevel;
 public:
  Banker(string filename);
  bool isInSafeState();
  bool isInSafeState2();
  void showSafeProcesses();
  void setInfoLevel(InfoLevel);
  int getNumberProcess() const;
  int getNumberKndResources() const;
  void evalRequirement(int* requirement, int nroReq, int nProcess);
  class BankerException : public exception {
  public:
    BankerException(ReasonException r, const char* msg) throw();
    virtual ~BankerException() throw();
    virtual const char* what() const throw();
  private:
    char *message;
    ReasonException re;
  };
};

