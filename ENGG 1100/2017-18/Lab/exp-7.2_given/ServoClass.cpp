#include "Arduino.h"
#include "ServoClass.h"

ServoClass::ServoClass(int pin)
{
	m_Pin = pin;	
  m_Min = 0;
  m_Max = 180;
}

void ServoClass::init()
{
  m_Servo.attach(m_Pin);
}
	
void ServoClass::setValue(int value)
{
  if(value < m_Min)
    value = m_Min;
  else if (value > m_Max)
    value = m_Max;
    
  m_Servo.write(value);
}

