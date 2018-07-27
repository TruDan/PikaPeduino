// PikaProbe.h

#ifndef _PIKAPROBE_h
#define _PIKAPROBE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PikaProbeClass
{
	int ambientTemp, ambientHumidity;

private:
	int pinNo;

 protected:


 public:
	void init(int pinNo);
	void update();
};

extern PikaProbeClass PikaProbe;

#endif

