// 
// 
// 

#include "FSMClass.h"

FSMClass FSM;

void FSMClass::init(fpState S)
{
	this->transit(S);
}

void FSMClass::transit(fpState S)
{
	m_fState = S;	// change function pointer.
	m_transited = true;
	m_timer.Start();
}

void FSMClass::run()
{
	if (m_transited == true)
		m_doTask = true;
	m_transited = false;
	m_fState();	// do task when function pointer change.
	m_doTask = false;
}

bool FSMClass::isDue(long duration)
{
	return m_timer.isDue(duration);
}
bool FSMClass::doTask()
{
	return m_doTask;
}

long FSMClass::getTime()
{
	return m_timer.getTime();
}
