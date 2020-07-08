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
long LinuxParser::Jiffies() {
  long jiffies = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    string Line;
    string Key;
    std::getline(stream, Line);
    std::istringstream LineStream(Line);
    std::map<CPUStates, long> States;
    LineStream >>
      Key >>
      States[kUser_] >>
      States[kNice_] >>
      States[kSystem_] >>
      States[kIdle_] >>
      States[kIOwait_] >>
      States[kIRQ_] >>
      States[kSoftIRQ_] >>
      States[kSteal_] >>
      States[kGuest_] >>
      States[kGuestNice_];
    if (Key == "cpu") {
      for (auto S : States) {
        jiffies += S.second;
      }
    }
  }
  return jiffies;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  long jiffies = 0;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    string Line;
    string Value;
    std::getline(stream, Line);
    std::istringstream linestream(Line);
    int n = 0;
    while (linestream >> Value && n++ < 15) {
      if (n == 14 || n == 15) {
        jiffies += std::atoi(Value.c_str());
      }
    }
  }
  return jiffies;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  return Jiffies() - IdleJiffies();
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  long jiffies = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    string Line;
    string Key;
    std::getline(stream, Line);
    std::istringstream LineStream(Line);
    std::map<CPUStates, long> States;
    LineStream >>
      Key >>
      States[kUser_] >>
      States[kNice_] >>
      States[kSystem_] >>
      States[kIdle_];
    if (Key == "cpu") {
      jiffies = States[kIdle_];
    }
  }
  return jiffies;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> ProcessorsStrings;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    string line;
    int i = 0;
    while (std::getline(stream, line)) {
      if (line.substr(0, 3) == "cpu") {
        if (++i > 1) {
          ProcessorsStrings.push_back(line);
        }
      }
      else {
        break;
      }
    }
  }
  return ProcessorsStrings;
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

  return line; 
  
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  
 string line;
  string s, ram;
  int value;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
      // getline(stream, line);<-- Please think about it, whether it is necessary ?
      // std::istringstream linestream(line);
      // linestream >> s; // When you do this then the linestream moves to the next character in the line but since you are not using this fact later and you are defining a new character, do you think it is necessary to declare "std::istringstream linestream(line)" here
      while (std::getline(stream, line)) {
          std::istringstream linestream(line);
          linestream >> s >> ram;
          if(s=="VmSize:"){
            return std::to_string(std::stol(ram)/1000);
          }
      }
    }  
  if (value == 0) {
    ram = "0.0";
  }
  return ram; 

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