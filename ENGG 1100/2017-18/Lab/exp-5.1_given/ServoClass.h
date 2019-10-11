#ifndef _Servo_h
#define _Servo_h
#include "Arduino.h"
#include <Servo.h>

// For IR Sensor, LED on = high, LEG off = low.

class ServoClass
{
protected:
    int m_Pin;	// 
    Servo m_Servo;
    int m_Min, m_Max;
    
  public:
    ServoClass(int pin);
    void init();
    void setValue(int value);
};

#endif
