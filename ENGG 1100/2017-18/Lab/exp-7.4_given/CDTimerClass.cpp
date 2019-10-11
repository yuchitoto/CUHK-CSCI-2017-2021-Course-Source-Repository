// 
// 
// 

#include "CDTimerClass.h"


CDTimerClass CDTimer;

bool CDTimerClass::Start(long duration)
{
	m_Start = millis();
	m_time = duration;
	return true;
}

bool CDTimerClass::Start()
{
	return Start(0);
}

bool CDTimerClass::isDue(long duration)
{
	if (millis() >= m_Start + m_time + duration)
		return true;
	else
		return false;
}
long CDTimerClass::getTime()
{
	return millis() - m_Start;
}
bool CDTimerClass::isDue()
{
	return isDue(0);
}

