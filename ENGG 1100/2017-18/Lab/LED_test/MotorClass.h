#ifndef _Motor_h
#define _Motor_h
#include "Arduino.h"

class MotorClass
{
protected:
    int m_DPin;	// Direction Pin
    int m_SPin;	// Speed Pin
    int m_maxSpeed;
    int m_minSpeed;
	int m_Speed;
    
  public:
    MotorClass(int Dpin, int Spin);
    void setSpeed(int SPEED);
    void setProperties(int maxSPEED, int minSPEED);
    int getSpeed();  
};

#endif
