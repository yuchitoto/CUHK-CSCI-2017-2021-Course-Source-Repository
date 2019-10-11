/*
  ENGG1100 Experiment-7.2, This FSM has one state only for motor testing
  Board: Arduino Nano
  Version: 20180227

Output, motor : D3,D2 and D5,D4 
*/
#include "ENGG1100.h"
  
FSMClass FSM1;          //The given FSM is named 'FSM1'.
TM1637DisplayClass LEDDisplay(D10,D11); //7-segment LED Display is connected to D10,D11 for debug
MotorClass MotorR(D3,D2);
MotorClass MotorL(D5,D4);

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);          //optional, for debug
  LEDDisplay.setBrightness(15); //optional
  FSM1.init(S_999);           // must have this line, you can change the first state of the FSM
}

void loop()
{
    FSM1.run(); //important, don't modify this line              
}
//================= Students add STATES below this line ====================
//----------start of state S_999 -----
void S_999()   
{
  if(FSM1.doTask())
  {
    MotorR.setSpeed(255);
    MotorL.setSpeed(255);
    LEDDisplay.setValue(255); 
  }
  if (FSM1.getTime() >2000) FSM1.transit(S_000);
}
void S_000()   
{
  if(FSM1.doTask())
  {
    MotorR.setSpeed(0);
    MotorL.setSpeed(0);
    LEDDisplay.setValue(0); 
  }
}

