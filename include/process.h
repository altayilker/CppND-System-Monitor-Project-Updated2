#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "process.h"
#include "linux_parser.h"


/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               // TODO: See src/process.cpp
  void set_Pid(int x);
  std::string User();                      // TODO: See src/process.cpp
  void set_User();
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process & a);  // TODO: See src/process.cpp  
  //bool operator>(Process & a);  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
    int pid_;
    std::string user_;
    float cpu_;
    std::string ram_;
    long int time_;
    string command_;

};

#endif