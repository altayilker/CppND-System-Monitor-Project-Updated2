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

// TODO: Return this process's ID
int Process::Pid() { return (LinuxParser::Pids())[Process::pid_]; } // (LinuxParser::Pids())[Process::pid]

void Process::set_Pid(int x){

    Process::pid_ = LinuxParser::Pids()[x];
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 

    return 0.12; 
    
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::pid_); }  // LinuxParser::Command(Process::pid)

// TODO: Return this process's memory utilization
string Process::Ram() { 
    
    // std::cout << "LinuxParser::Ram(Process::pid): " << LinuxParser::Ram(Process::pid) << "\n";
    return LinuxParser::Ram(Process::pid_); 

} // LinuxParser::Ram(Process::pid)

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::pid_); }  // LinuxParser::User()

void Process::set_User(int x){
 
    Process::user_ = LinuxParser::User(Process::pid_); 

}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::pid_); }  // LinuxParser::UpTime()

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const 
{ 
        return true;

}