#include "debugtracer.h"
#include "Arduino.h"
#include <string>

DebugTracer::DebugTracer () 
  : mLiquidCrystalDisplay(12, 11, 5, 4, 3, 2)
{
  mLiquidCrystalDisplay.begin(16, 2);
  //Serial.begin(9600);
}

DebugTracer& DebugTracer::getInstance ()
{
  // Instantiated on first use:
  // Guaranteed to be destroyed.
  static DebugTracer instance;
  return instance;
}


void DebugTracer::printDebug (const std::string& information) 
{
  mLiquidCrystalDisplay.print(information.c_str());
  //Serial.println(information.c_str());
}
