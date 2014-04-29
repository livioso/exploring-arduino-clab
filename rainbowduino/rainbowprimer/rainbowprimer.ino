#include <Rainbowduino.h>

void setup() 
{
  // initialize rainbowduino
  Rb.init();
}
 
void loop()
{
  // loop through all led's and set a color for each
  for(int x=0; x<8; x++) {
    for(int y=0; y<8; y++) {
      Rb.setPixelXY(x, y, 0xFF0000);
    }
  }
}
