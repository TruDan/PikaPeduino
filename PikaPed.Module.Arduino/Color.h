// ColorClass.h

#ifndef _COLOR_h
#define _COLOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Color
{
 public:
	 byte R, G, B;
	Color(byte r, byte g, byte b);
};

#endif

