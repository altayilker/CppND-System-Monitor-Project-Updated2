#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include <unistd.h>
#include "format.h"
#include <array>
#include <thread>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

std::array<int,10> cpu_last = {};
int cpu_last_sum = 0;


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return version;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 

  string key;
  float value;
  float MemTotal;
  float MemFree;
  string line;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (filestream.is_open()) {
      while (std::getline(filestream, line)) {

        std::istringstream linestream(line);
        while (linestream >> key >> value) {
            if (key == "MemTotal:") 
              MemTotal = value;
            if (key == "MemFree:") 
              MemFree = value;

        }
      }
  }

  float Total_used_memory = MemTotal - MemFree;

  return Total_used_memory/MemTotal; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  
  string line;
  long uptime, idle_time;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idle_time;
  }
  // std::cout << "uptime "<< uptime << "\n";

  return uptime;

}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
void LinuxParser::CpuUtilization(){
  /* vector<string> data;
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 0; i <= 10; i++) {
    	linestream >> value;
      	data.push_back(value);
    }
  }
  data.erase(data.begin());
  return data;
  */
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key;
  int value;
  string line;
  int processes;

  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
      while (std::getline(filestream, line)) {

        std::istringstream linestream(line);
        while (linestream >> key >> value) {
            if (key == "processes") 
              processes = value;

        }
      }
  }

  return processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key;
  float value;
  string line;
  int processes;

  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
      while (std::getline(filestream, line)) {

        std::istringstream linestream(line);
        while (linestream >> key >> value) {
            if (key == "procs_running") 
              processes = value;

        }
      }
  }

  return processes; 

 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  
  string line;

  std::string s = std::to_string(pid);
  std::ifstream stream(kProcDirectory + s + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  //std::cout << "kProcDirectory + s + kCmdlineFilename: " << kProcDirectory + s + kCmdlineFilename << "\n";
  //std::cout << "line: " << line << "\n";

  return line; 
  
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  
  string key;
  int value;
  string line;
  int processes;

  std::string s = std::to_string(pid);
  std::ifstream filestream(kProcDirectory + s + kStatusFilename);

  if (filestream.is_open()) {
      while (std::getline(filestream, line)) {

        std::istringstream linestream(line);
        while (linestream >> key >> value) {
            if (key == "VmSize:") 
              processes = value*0.001;

        }
      }
  }

  return to_string(processes); 

}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  
  string key;
  int value;
  string line;
  int processes;

  std::string s = std::to_string(pid);
  std::ifstream filestream(kProcDirectory + s + kStatusFilename);

  if (filestream.is_open()) {
      while (std::getline(filestream, line)) {

        std::istringstream linestream(line);
        while (linestream >> key >> value) {
            if (key == "Uid:") 
              processes = value;

        }
      }
  }

  return to_string(processes);

}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  
  string line;
  string key;
  string value1, value2, value3;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value1 >> value2   ) {
        if (value1 == "x" && value2 == (LinuxParser::Uid(pid))) {

          return key;
        }
      }
    }
  }
 return key;
  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  
  string line;
  long clock_ticks;

  std::string s = std::to_string(pid);
  std::ifstream stream(kProcDirectory + s + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  std::istringstream linestream(line);
  for (int i = 0; i < 23; ++i){
    linestream >> clock_ticks;
    if(i == 22)
      break; 
  }
  
  // std::cout << "uptime: " <<  Format::ElapsedTime(clock_ticks/sysconf(_SC_CLK_TCK)) << "\n";
  return clock_ticks/sysconf(_SC_CLK_TCK);  // do we need ? 
  
}