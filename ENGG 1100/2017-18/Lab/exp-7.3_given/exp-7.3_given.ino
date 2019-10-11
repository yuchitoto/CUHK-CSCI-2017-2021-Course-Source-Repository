/*
  ENGG1100 Experiment-7.3, This FSM has one state only for motor testing
  Board: Arduino Nano
  Version: 20180227
Output, motor : D3,D2 and D5,D4 
*/
#include "ENGG1100.h"
  
FSMClass FSM1;          //The given FSM is named 'FSM1'.
TM1637DisplayClass LEDDisplay(D10,D11); //7-segment LED Display is connected to D10,D11 for debug
MotorClass MotorR(3,2);
MotorClass MotorL(5,4);

//Servo ServoClass;  // enable this line for exp-7.4
int MRspeed = 255;  //variable for motorR speed
int MLspeed = 255;  //variable for motorL speed

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
    MotorR.setSpeed(MRspeed);
    MotorL.setSpeed(MLspeed);
    LEDDisplay.showNumberDec(MRspeed, true); 
  }
if (FSM1.getTime() >1000) FSM1.transit(S_111);  //one-state-loop, students have to modify this line
}
void S_111()   
{
  if(FSM1.doTask())
  {
    MRspeed--;
    MLspeed--;
    if(MRspeed<0)MRspeed = 0;
    if(MLspeed<0)MLspeed = 0;
  }
FSM1.transit(S_999);  //one-state-loop, students have to modify this line
}

