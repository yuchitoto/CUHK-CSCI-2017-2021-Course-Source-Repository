#ifndef _OutputClass_h
#define _OutputClass_h
#include "Arduino.h"


class OutputClass
{
protected:
    int m_Pin;	// 
    int m_Value;
    bool isValue();
    
  public:
    OutputClass(int pin);
	  bool getHiLow();  
    int getValue();
    void setHiLow(bool b);
    bool setValue(int i);
};

#endif
