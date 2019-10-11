// 
// 
// 

#include "UltrasoundSensorClass.h"

UltrasoundSensorClass::UltrasoundSensorClass(uint8_t Pecho, uint8_t Ptrig)
{
	this->m_Pecho = Pecho;
	this->m_Ptrig = Ptrig;
	pinMode(this->m_Ptrig, OUTPUT);
	pinMode(this->m_Pecho, INPUT);	
}

void UltrasoundSensorClass::setTimeout(unsigned long timeout)
{
	this->m_Timeout = timeout;
}
void UltrasoundSensorClass::setDistanceLimit(int dist)
{
  if(dist>400 || dist<0)
    dist = 400;
  float timeout = (dist*2000/100)/340+1;
  this->setTimeout(timeout*1000);
}

float UltrasoundSensorClass::getDistance()
{
		this->trigger();
		state = LOW;
		pre_state = state;
		//return pulseIn(m_Pecho, HIGH);
		//*
		do {
			state = digitalRead(m_Pecho);
			if (state == HIGH && pre_state == LOW)
			{
				stime = micros();
			}
			else if (stime>0 && state == LOW && pre_state == HIGH)
			{
				etime = micros();
				return (etime - stime)*0.017;
			}
			pre_state = state;
		} while (micros() <= time + m_Timeout);
		//*/
		//timeout result.
   delay(100);
		return 999;
}



bool UltrasoundSensorClass::trigger()
{
	etime = 0;
	stime = 0;
	//init a trig pulse for 10us	
	digitalWrite(m_Ptrig, HIGH);
	//log time
	delayMicroseconds(10);
	digitalWrite(m_Ptrig, LOW);
	time = micros();
	return false;
}

