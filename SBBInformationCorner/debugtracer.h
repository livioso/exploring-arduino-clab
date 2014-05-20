#pragma once

#include <string>

class DebugTracer {
  
  public:
   
    // get the singleton and 
    // instantiate it on the first call
    static DebugTracer& getInstance ();

    // print the debug information to the serial port 9600
    void printDebug (const std::string& information);

  private:
    
    DebugTracer ();

    // copying the singleton is not allowed
    DebugTracer (DebugTracer const&);

    // same applies to copies due to assignments 
    void operator= (DebugTracer const&);
};
