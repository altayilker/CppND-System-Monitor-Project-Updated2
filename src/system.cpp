#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    
    processes_.clear(); // when erased, changes in the process queue changes.
    vector<int> processes = LinuxParser::Pids();
     
    for(int i = 0; i < processes.size(); i++){
        processes_.push_back(Process(processes[i]));
    }
    
    for(int i = 0; i < processes.size(); i++){
        processes_[i].User();
        processes_[i].CpuUtilization();
        processes_[i].Ram();
        processes_[i].UpTime();
        processes_[i].Command();
    }
    sort(processes_.begin(),processes_.end());
    return processes_;

}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::CpuUtilization() { 
    
    /*
    
    https://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-using-c/3017438#3017438

    CPUSnapshot previousSnap;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    CPUSnapshot curSnap;

    const float ACTIVE_TIME = curSnap.GetActiveTimeTotal() - previousSnap.GetActiveTimeTotal();
    const float IDLE_TIME   = curSnap.GetIdleTimeTotal() - previousSnap.GetIdleTimeTotal();
    const float TOTAL_TIME  = ACTIVE_TIME + IDLE_TIME;
    int usage = 100.f * ACTIVE_TIME / TOTAL_TIME;
    std::cout << "total cpu usage: " << usage << std::endl;

    */
   return 0.18; // LinuxParser::CpuUtilization();
    
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
