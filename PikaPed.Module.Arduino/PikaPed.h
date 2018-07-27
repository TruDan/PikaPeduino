// PikaPed.h

#ifndef _PIKAPED_h
#define _PIKAPED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PikaPedClass
{
 protected:


 public:
	void init();
	void update();

};

extern PikaPedClass PikaPed;

#endif

