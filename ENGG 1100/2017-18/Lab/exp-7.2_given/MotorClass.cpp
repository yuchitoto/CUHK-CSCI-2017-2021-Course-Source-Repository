#include "Arduino.h"
#include "MotorClass.h"

MotorClass::MotorClass(int Spin, int Dpin)
{
  m_DPin = Dpin;
  m_SPin = Spin;
  m_Speed = 0;
  setProperties(255, -255);
  pinMode(m_DPin, OUTPUT);
  pinMode(m_SPin, OUTPUT);
  setSpeed(0);
}

void MotorClass::setSpeed(int SPEED)
{
	m_Speed = SPEED;
  if(m_Speed>m_maxSpeed)
    m_Speed = m_maxSpeed;
  if (m_Speed < m_minSpeed)
    m_Speed = m_minSpeed;
  if (m_Speed>=0)
  {
    analogWrite(m_SPin, m_Speed);
    digitalWrite(m_DPin, LOW);
  }else
  {
    analogWrite(m_SPin, 255+m_Speed);
    digitalWrite(m_DPin, HIGH);
  }
}
void MotorClass::setProperties(int maxSPEED, int minSPEED)
{
  m_maxSpeed = maxSPEED; m_minSpeed = minSPEED; 
  setSpeed(m_Speed);
}

int MotorClass::getSpeed()
{
	return m_Speed;
}
