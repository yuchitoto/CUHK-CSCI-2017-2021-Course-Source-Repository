/*
  ENGG1100 Experiment-6.2, This is a one-state-loop FSM program for ENGG1100 to show measured sonic data on 7-sengment display
  Board: Arduino Nano
  Version: 20170706_AlexSiu

  Output, 7-segment display: D10,D11
  Input, sonic sensor: D12,D13
*/
#include "ENGG1100.h"

FSMClass FSM1;          //The given FSM is named 'FSM1'.
UltrasoundSensorClass Sonic(D12, D13); //sonic sensor is connected to D12,D13
TM1637DisplayClass LEDDisplay(D10, D11); //7-segment LED Display is connected to D10,D11 for debug
float distance = 0;  //variable

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);          //optional, for debug
  LEDDisplay.setBrightness(15); //optional
  //Sonic.setDistanceLimit(20); // optional,set a rough measure limit to 20cm
  FSM1.init(S_start);           // must have this line, you can change the first state of the FSM
}

void loop()
{
  FSM1.run(); //important, don't modify this line
}
//================= Students add STATES below this line ====================
//----------start of state S_DRed -----
void S_start()    // This state the driver light RED lit.
{
  if (FSM1.doTask())
  {
    distance = Sonic.getDistance() * 10; //the result of getDistance() is cm, shown in mm (x10)
    LEDDisplay.setValue(distance); //show the current state on LED display module
  }
  if (FSM1.getTime() > 500)  FSM1.transit(S_start); //one-state-loop, re-enter to current state when time is up
}

