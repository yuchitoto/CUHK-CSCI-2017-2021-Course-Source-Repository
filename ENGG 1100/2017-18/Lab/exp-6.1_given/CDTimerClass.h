// Timer.h
//This Timer has two types.
//1. Count down timer:
//	Use Start(duration) to set count down and isDue to check wheather timer due or not.
//2. Normal Timer:
//  User Start() to start the timer, and isDue(duration) to check the duration.

#ifndef _CDTIMER_h
#define _CDTIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class CDTimerClass
{
 protected:
	unsigned long m_Start;	// set start millis
	unsigned long m_time = 0;	// set count down value.

 public:
	//Method 1.
	bool Start(long duration);
	bool isDue();
	//Method 2.
	bool Start();
	bool isDue(long duration);
	long getTime();
 

};

// one Object as a sample.
extern CDTimerClass CDTimer;

#endif

