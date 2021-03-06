#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;


Process::Process(int pid):pid_(pid){}


// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// int Process::Pid() { return (LinuxParser::Pids())[Process::pid_]; } // (LinuxParser::Pids())[Process::pid]

void Process::set_Pid(int x){

    Process::pid_ = LinuxParser::Pids()[x];
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 

    long total = LinuxParser::ActiveJiffies(pid_);
    float sec = LinuxParser::UpTime() - LinuxParser::UpTime(pid_);
    return cpu_ = float(total)/sysconf(_SC_CLK_TCK)/sec;
}

string Process::Command() { return command_ = LinuxParser::Command(Process::pid_); }  // LinuxParser::Command(Process::pid)

// TODO: Return this process's memory utilization
string Process::Ram() { return ram_ = LinuxParser::Ram(Process::pid_); } 


// TODO: Return the user (name) that generated this process
string Process::User() { return user_ = LinuxParser::User(Process::pid_); }  // LinuxParser::User()


// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return time_ = LinuxParser::UpTime() -  LinuxParser::UpTime(Process::pid_); }  // LinuxParser::UpTime()

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function

bool Process::operator<(Process& a) {
    return LinuxParser::ActiveJiffies(pid_) > LinuxParser::ActiveJiffies(a.pid_);
}