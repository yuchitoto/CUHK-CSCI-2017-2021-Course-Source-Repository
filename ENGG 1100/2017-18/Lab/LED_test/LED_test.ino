/*
  ENGG1100 Experiment-6.2, This is a one-state-loop FSM program for ENGG1100 to show measured sonic data on 7-sengment display
  Board: Arduino Nano
  Version: 20170706_AlexSiu

Output, 7-segment display: D10,D11 
Input, sonic sensor: D12,D13
*/
#include "ENGG1100.h"
  
FSMClass FSM1;          //The given FSM is named 'FSM1'.
UltrasoundSensorClass Sonic(D12,D13); //sonic sensor is connected to D12,D13
TM1637DisplayClass LEDDisplay(D10,D11); //7-segment LED Display is connected to D10,D11 for debug
OutputClass spot1(A2);
OutputClass spot2(A3);
float distance = 0;  //variable

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);          //optional, for debug
  LEDDisplay.setBrightness(15); //optional
  //Sonic.setDistanceLimit(20); // optional,set a rough measure limit to 20cm
  FSM1.init(S_0);           // must have this line, you can change the first state of the FSM
}

void loop()
{
    FSM1.run(); //important, don't modify this line              
}
//================= Students add STATES below this line ====================
//----------start of state S_DRed -----
void S_0()    // This state the driver light RED lit.
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(0000);//show the current state on LED display module
    spot1.setHiLow(1);
    spot2.setHiLow(1);
  }
  if (FSM1.getTime() >1000)  FSM1.transit(S_1); //one-state-loop, re-enter to current state when time is up
}
void S_1()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(0001);
    spot1.setHiLow(1);
    spot2.setHiLow(0);
  }
  if(FSM1.getTime() >1000) FSM1.transit(S_2);
}
void S_2()
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1030);
    spot1.setHiLow(0);
    spot2.setHiLow(1);
  }
  if(FSM1.getTime() >1000) FSM1.transit(S_0);
}

