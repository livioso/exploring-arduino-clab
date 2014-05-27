#include "LCD.h"
#include "Arduino.h"
#include <string>

LCD::LCD () 
  : mLiquidCrystalDisplay(12, 11, 5, 4, 3, 2)
{
  mLiquidCrystalDisplay.begin(16, 2);
  mLiquidCrystalDisplay.print("ho");
  //Serial.begin(9600);
}

LCD& LCD::getInstance ()
{
  // Instantiated on first use:
  // Guaranteed to be destroyed.
  static LCD instance;
  
  return instance;
}


void LCD::printMessage (const std::string& information) 
{
  //mLiquidCrystalDisplay.print(information.c_str());
  Serial.println(information.c_str());
}
