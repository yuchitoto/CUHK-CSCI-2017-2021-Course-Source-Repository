// UltrasoundSensorClass.h

#ifndef _ULTRASOUNDSENSOR_h
#define _ULTRASOUNDSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class UltrasoundSensorClass
{
 protected:
	 uint8_t m_Pecho;
	 uint8_t m_Ptrig;
	 unsigned long m_Timeout = 30000;
	 unsigned long time, stime, etime;
	 bool state, pre_state = LOW;
	 bool trigger();
   void setTimeout(unsigned long timeout);
  
 public:
  UltrasoundSensorClass(uint8_t Pecho, uint8_t Ptrig);
//	void init(uint8_t Pecho, uint8_t Ptrig );
  void setDistanceLimit(int dist);
	float getDistance();	//Return calculated distance (cm) or -1 if timeout.
	//By Calculation, the speed of sound is 340m/s.
	// The max range is ~4m
	// maximum delay time should be 4*2/340 = 23(ms) ~25000microsecond
	// Distance(cm) traveled in 1microsecond = (340/2)*100 /1,000,000
};


#endif

