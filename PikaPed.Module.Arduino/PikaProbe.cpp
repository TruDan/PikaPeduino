// 
// 
// 

#include "PikaProbe.h"

#include <dht.h>

void PikaProbeClass::init(int pinNo)
{
	this->pinNo = pinNo;

}

void PikaProbeClass::update()
{
	//int chk = DHT.read11(this->pinNo);

	//this->ambientTemp = int(DHT.temperature);
	//this->ambientHumidity = int(DHT.humidity);
}



PikaProbeClass PikaProbe;

