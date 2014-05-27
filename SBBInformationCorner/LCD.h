#pragma once

#include <string>
#include <LiquidCrystal.h>

class LCD {
  
  public:
   
    // get the singleton and 
    // instantiate it on the first call
    static LCD& getInstance ();

    // print the debug information to the serial port 9600
    void printMessage (const std::string& information);

  private:
  
    LiquidCrystal mLiquidCrystalDisplay;
    
    LCD ();

    // copying the singleton is not allowed
    LCD (LCD const&);

    // same applies to copies due to assignments 
    void operator= (LCD const&);
};
