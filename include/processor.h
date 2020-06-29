#ifndef PROCESSOR_H
#define PROCESSOR_H
# include <linux_parser.h>
#include <unordered_map>

class Processor {
 public:
   double Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
    private:
    long anteriorTotal{0};
    long anteriorActive{0};

};

#endif