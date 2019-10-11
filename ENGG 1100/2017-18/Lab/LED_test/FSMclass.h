// FSM.h
// Usage:
// 1. Declare a Finite state machine object : (code) FSMClass FSMSample
// 2. Create function as first state: (code) void FSMSampleState1(bool task)
// 2. Create function as second state: (code) void FSMSampleState2(bool task)
// 2.1 Take a look of the function sample
// 2. Initialize FSM in setup() function : (code)  FSMSample.init(FSMSampleState1);
// 3. Execute the FSM in run() function : FSMSample.run();

#ifndef _FSM_h
#define _FSM_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "CDTimerClass.h"

typedef void(*fpState) (void);

class FSMClass
{
protected:
	fpState m_fState;	//Function pointer
	bool m_transited;	//Set to true when funtion pointer transited.
	bool m_doTask;
	CDTimerClass m_timer;
public:
	void init(fpState S);		// get initizlise function pointer.
	void transit(fpState S);	// transite state(change function pointer).
	void run();					// run the function pointer.
	bool isDue(long duration);	// check timer with duration.
	bool doTask();
	long getTime();
};

extern FSMClass FSM;
/*
//2.1 Take a State function sample
FSMClass FSMSample;
void FSMSampleState1(bool task)
{
if (task)	// this is required.
{
// Put what you want to do here.
}
//set condition to leave this state
if (FSMSample.getTime() == 1000)	// 1000ms = 1second
FSMSample.transit(FSMSampleState2)
}
void FSMSampleState2(bool task)
{
if (task)	// this is required.
{
// Put what you want to do here.
}
//set condition to leave this state
if (FSMSample.getTime() == 2000)	// 2000ms = 2second
FSMSample.transit(FSMSampleState1)
}
*/
#endif

