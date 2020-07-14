#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { vector<string> cpu_string=LinuxParser::CpuUtilization();
    vector<float> cpu_float;
    for( unsigned int i=0;i< cpu_string.size();i++){
 
       float x= std::stof(cpu_string[i]);
        cpu_float.push_back(x);
    }
    float NonIdle=cpu_float[LinuxParser::CPUStates::kUser_]+cpu_float[LinuxParser::CPUStates::kNice_]+
    cpu_float[LinuxParser::CPUStates::kSystem_]+cpu_float[LinuxParser::CPUStates::kIRQ_]+
    cpu_float[LinuxParser::CPUStates::kSoftIRQ_]+cpu_float[LinuxParser::CPUStates::kSteal_];

     float Idle=cpu_float[LinuxParser::CPUStates::kIdle_]+cpu_float[LinuxParser::CPUStates::kIOwait_];
     float Total=NonIdle+Idle;
      if(Total>0)                          
        cpu_percentage=(Total-Idle)/Total;
    
    return cpu_percentage;                           
}