#ifndef _Sensor_h
#define _Sensor_h
#include "Arduino.h"
// For IR Sensor, LED on = high, LEG off = low.

class SensorClass
{
protected:
    int m_Pin;	// 
    
  public:
    SensorClass(int pin);
	  bool getHiLow();  
    int getValue();
};

#endif
