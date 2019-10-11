#include "Arduino.h"
#include "OutputClass.h"

OutputClass::OutputClass(int pin)
{
	m_Pin = pin;
  m_Value = 0;
  pinMode(m_Pin, OUTPUT);
  digitalWrite(m_Pin, LOW);  
}

bool OutputClass::isValue()
{
  switch (m_Pin) {
    case 3:
    case 5:
    case 6:
    case 9:
    case 10:
    case 11:
      return true;
    break;
    default:
      return false;
    break;
  }
}
  
bool OutputClass::getHiLow()
{
  if(m_Value ==0)
    return false;
  return true;
}
int OutputClass::getValue()
{
  return m_Value;
}

void OutputClass::setHiLow(bool b)
{
  if(b == false)
  {
    digitalWrite(m_Pin, LOW);
    m_Value = 0;
  }else
  {    
    digitalWrite(m_Pin, HIGH);
    m_Value = 1;
  }
}

bool OutputClass::setValue(int i)
{
  if (isValue())
  {
    m_Value = i;
    analogWrite(m_Pin, m_Value); 
    return true;
  }
  return false;
}

