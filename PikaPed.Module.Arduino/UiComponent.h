// UiComponent.h

#ifndef _UICOMPONENT_h
#define _UICOMPONENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class UiComponentClass
{
 protected:


 public:
	 int X, Y, Width, Height;

	 void init(int x, int y, int width, int height);
	 void update();
	 void draw();
};

extern UiComponentClass UiComponent;

#endif

