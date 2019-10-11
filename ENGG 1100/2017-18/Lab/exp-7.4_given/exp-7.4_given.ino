/*
  ENGG1100 Experiment-7.4, This FSM has one state only for SERVO testing
  Board: Arduino Nano
  Version: 20170717_AlexSiu

Output, Servo : D9
*/
#include "ENGG1100.h"
#include <Servo.h>
  
FSMClass FSM1;          //The given FSM is named 'FSM1'.
TM1637DisplayClass LEDDisplay(D10,D11); //7-segment LED Display is connected to D10,D11 for debug
ServoClass Servo1(D9);
//SensorClass S1(A5); // Sensor S1 the left most sensor on the smart car

int angle=10;

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);          //optional, for debug
  LEDDisplay.setBrightness(15); //optional
  FSM1.init(S_999);           // must have this line, you can change the first state of the FSM
  Servo1.init();
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
    Servo1.setValue(angle);
    LEDDisplay.setValue(angle); 
  }
// if (.....) FSM1.transit(S_999);  //one-state-loop, students have to modify this line
}

