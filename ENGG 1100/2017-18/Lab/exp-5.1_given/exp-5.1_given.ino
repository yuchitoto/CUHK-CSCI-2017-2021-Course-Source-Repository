/*
  ENGG1100 Experiment-5.1, This is a triffic light program for ENGG1100 to show Finite-State-Machine
  Board: Arduino Nano
  Version: 20170718_AlexSiu

Outputs, LEDs: LED1(DriverRed), LED2(DriverAmber), LED3(DriverGreen)
               LED4(PedestrainRed) and LED5(PedestrainGreen)
FSM states (4 states): RED > RED+AMBER > GREEN > AMBER > RED for drivers' lights
  Some libraries are not be used in this experiment they are marked with "//", 
  remove "//" to enable the lines as you want
*/
#include "ENGG1100.h"
  
FSMClass FSM1;          //The given FSM is named 'FSM1'.
OutputClass DRed(A1);   //Driver Traffic light - Red
OutputClass DAmber(A2); //Driver Traffic light - Amber
OutputClass DGreen(A3); //Driver Traffic light - Green
//OutputClass PRed(A4); //Pedestrain light - Red
//OutputClass PGreen(A5); //Pedestrain light - Greend
//SensorClass SW14(A6); // A sensor for car detecting
//SensorClass SW15(A7); // A switch for pedestrains
TM1637DisplayClass LEDDisplay(D10,D11); //7-segment LED Display for debug
//int flash = 0;

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);          //optional, for debug
  LEDDisplay.setBrightness(15); //optional
  FSM1.init(S_DRed);            // must have this line, you can change the first state of the FSM
}

void loop()
{
    FSM1.run(); //important, don't modify this line              
}
//================= Students add STATES below this line ====================
//----------start of state S_DRed -----
void S_DRed()    // This state the driver light RED lit.
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(101); //show the current state on LED display module
    DRed.setHiLow(1);
    DAmber.setHiLow(0);   
    DGreen.setHiLow(0);
    //PRed.setHiLow(0);
    //PGreen.setHiLow(1);
    //flash=0;
  }
  if (FSM1.getTime() >5000)  FSM1.transit(S_DRedAmber); //this state will be kept for 5sec.
  // if (SW14.getHiLow()==1 && FSM1.getTime() > 1000) FSM1.transit(S_DRedAmber);
}
//----------start of state S_DRedAmber ------
void S_DRedAmber()  // This state the driver light RED and AMBER lit.
{
  if(FSM1.doTask())
  {
    DRed.setHiLow(1);
    DAmber.setHiLow(1);   
    DGreen.setHiLow(0);
    LEDDisplay.setValue(102);    //show the current state on LED display module
  }
  if (FSM1.getTime() >1000) FSM1.transit(S_DGreen); //this state will be kept for 1sec.
}
//----------start of state S_DGreen -----
void S_DGreen()  // This state the driver light GREEN lit.
{
  if(FSM1.doTask())
  {
    DRed.setHiLow(0);
    DAmber.setHiLow(0);   
    DGreen.setHiLow(1);
    LEDDisplay.setValue(103);    //show the current state on LED display module
  }
  if (FSM1.getTime() >10000)  FSM1.transit(S_DAmber); //this state will be kept for 10sec.
}
//----------start of state S_DAmber -----
void S_DAmber()  // This state the driver light AMber lit.
{
  if(FSM1.doTask())
  {
    DRed.setHiLow(0);
    DAmber.setHiLow(1);   
    DGreen.setHiLow(0);
    LEDDisplay.setValue(104);    //show the current state on LED display module
  }
  if (FSM1.getTime() >1000)  FSM1.transit(S_DRed);  //this state will be kept for 1sec.
}
//---------- end of program -----

