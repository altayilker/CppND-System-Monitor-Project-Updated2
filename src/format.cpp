#include <string>

#include "format.h"
#include <iostream>
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
  int hour, minute, secs;

  hour = seconds/3600;
  minute = (seconds - hour*3600)/60;
  secs = seconds - hour*3600 - minute*60;


  string s_hour = std::to_string(hour);
  string s_minute = std::to_string(minute);
  string s_secs = std::to_string(secs);
  string total_time = s_hour + ":" + s_minute + ":" + s_secs;

  return total_time;
 
}