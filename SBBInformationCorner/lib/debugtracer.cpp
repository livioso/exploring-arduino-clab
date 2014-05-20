#include "debugtracer.h"
#include "Arduino.h"

DebugTracer::DebugTracer () 
{
	Serial.begin(9600);
}

DebugTracer& DebugTracer::getInstance ()
{
	// Instantiated on first use:
	// Guaranteed to be destroyed.
	static DebugTracer instance;
	return instance;
}


void DebugTracer::printDebug (std::string information) 
{
	Serial.println(information);
}