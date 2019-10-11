#include "Arduino.h"
#include "SensorClass.h"

SensorClass::SensorClass(int pin)
{
	m_Pin = pin;
  pinMode(m_Pin, INPUT);
}
  
bool SensorClass::getHiLow()
{
	if (m_Pin == A6 || m_Pin == A7) {
		if (analogRead(m_Pin) > 512 ) return true;
		else return false;
	}
	else return digitalRead(m_Pin);
	
}

int SensorClass::getValue()
{
  switch (m_Pin) {
    case A0:
    case A1:
    case A2:
    case A3:
    case A4:
    case A5:
    case A6:
    case A7:
      return analogRead(m_Pin);
    break;
    default:
      return getHiLow();
    break;
  }
}

