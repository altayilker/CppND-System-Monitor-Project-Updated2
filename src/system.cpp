#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
using namespace std;

System::System() {
	for(int pid: LinuxParser::Pids()) {
    	processes_.push_back(Process(pid));
    }
}


Processor& System::Cpu() { 
    std::vector<string> utilizations = LinuxParser::CpuUtilization();
    utilizations.clear();
    return cpu_;
}


vector<Process>& System::Processes() { 
    sort(processes_.begin(), processes_.end());
    return processes_; 
}

std::string System::Kernel() { return LinuxParser::Kernel(); }


float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }


std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }


int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }


int System::TotalProcesses() { return processes_.size(); }


long int System::UpTime() { return LinuxParser::UpTime(); }
