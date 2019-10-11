/*
Output, 7-segment display: D10,D11 
Input, IR sensor: A5,A4,A3,A2
*/
#include "ENGG1100.h"

#define WHT 1
#define BLK 0
SensorClass S1(A5), S2(A4), S3(A3), S4(A2);

FSMClass FSM1;          //The given FSM is named 'FSM1'.
UltrasoundSensorClass Sonic(D12,D13); //sonic sensor is connected to D12,D13
TM1637DisplayClass LEDDisplay(D10,D11); //7-segment LED Display is connected to D10,D11 for debug
float distance = 0;  //variable

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);          //optional, for debug
  LEDDisplay.setBrightness(15); //optional
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
  if(FSM1.doTask())
  {
    //LEDDisplay.setValue(9999);
  }
  if (S1.getHiLow()== WHT && S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== WHT) FSM1.transit(S_101);
  if (S1.getHiLow()== WHT && S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== BLK) FSM1.transit(S_102);
  if (S1.getHiLow()== WHT && S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== WHT) FSM1.transit(S_103);
  if (S1.getHiLow()== WHT && S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== BLK) FSM1.transit(S_104);
  if (S1.getHiLow()== WHT && S2.getHiLow()== BLK && S3.getHiLow()== WHT && S4.getHiLow()== WHT) FSM1.transit(S_105);
  if (S1.getHiLow()== WHT && S2.getHiLow()== BLK && S3.getHiLow()== WHT && S4.getHiLow()== BLK) FSM1.transit(S_106);
  if (S1.getHiLow()== WHT && S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== WHT) FSM1.transit(S_107);
  if (S1.getHiLow()== WHT && S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK) FSM1.transit(S_108);
  if (S1.getHiLow()== BLK && S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== WHT) FSM1.transit(S_109);
  if (S1.getHiLow()== BLK && S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== BLK) FSM1.transit(S_110);
  if (S1.getHiLow()== BLK && S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== WHT) FSM1.transit(S_111);
  if (S1.getHiLow()== BLK && S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== BLK) FSM1.transit(S_112);
  if (S1.getHiLow()== BLK && S2.getHiLow()== BLK && S3.getHiLow()== WHT && S4.getHiLow()== WHT) FSM1.transit(S_113);
  if (S1.getHiLow()== BLK && S2.getHiLow()== BLK && S3.getHiLow()== WHT && S4.getHiLow()== BLK) FSM1.transit(S_114);
  if (S1.getHiLow()== BLK && S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== WHT) FSM1.transit(S_115);
  if (S1.getHiLow()== BLK && S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK) FSM1.transit(S_116);
}
//------------------------------------
void S_101()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1111); 
  }
  if (!(S1.getHiLow()== WHT && S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== WHT)) FSM1.transit(S_start);   
}
//------------------------------------
void S_102()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1110); 
  }
  if (!(S1.getHiLow()== WHT && S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== BLK)) FSM1.transit(S_start);   
}
//------------------------------------
void S_103()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1101); 
  }
  if (!(S1.getHiLow()== WHT && S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== WHT)) FSM1.transit(S_start);   
}
//------------------------------------
void S_104()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1100); 
  }
  if (!(S1.getHiLow()== WHT && S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== BLK)) FSM1.transit(S_start);   
}
//------------------------------------
void S_105()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1011); 
  }
  if (!(S1.getHiLow()== WHT && S2.getHiLow()== BLK && S3.getHiLow()== WHT && S4.getHiLow()== WHT)) FSM1.transit(S_start);   
}
//------------------------------------
void S_106()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1010); 
  }
  if (!(S1.getHiLow()== WHT && S2.getHiLow()== BLK && S3.getHiLow()== WHT && S4.getHiLow()== BLK)) FSM1.transit(S_start);   
}
//------------------------------------
void S_107()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1001); 
  }
  if (!(S1.getHiLow()== WHT && S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== WHT)) FSM1.transit(S_start);   
}
//------------------------------------
void S_108()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(1000); 
  }
  if (!(S1.getHiLow()== WHT && S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK)) FSM1.transit(S_start);   
}
//------------------------------------
void S_109()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setDigit(0,0);
    LEDDisplay.setDigit(1,1);
    LEDDisplay.setDigit(1,2);
    LEDDisplay.setDigit(1,3); 
  }
  if (!(S1.getHiLow()== BLK && S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== WHT)) FSM1.transit(S_start);   
}
//------------------------------------
void S_110()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setDigit(0,0);
    LEDDisplay.setDigit(1,1);
    LEDDisplay.setDigit(1,2);
    LEDDisplay.setDigit(0,3);  
  }
  if (!(S1.getHiLow()== BLK && S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== BLK)) FSM1.transit(S_start);   
}
//------------------------------------
void S_111()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setDigit(0,0);
    LEDDisplay.setDigit(1,1);
    LEDDisplay.setDigit(0,2);
    LEDDisplay.setDigit(1,3);  
  }
  if (!(S1.getHiLow()== BLK && S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== WHT)) FSM1.transit(S_start);   
}
//------------------------------------
void S_112()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setDigit(0,0);
    LEDDisplay.setDigit(1,1);
    LEDDisplay.setDigit(0,2);
    LEDDisplay.setDigit(0,3);   
  }
  if (!(S1.getHiLow()== BLK && S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== BLK)) FSM1.transit(S_start);   
}
//------------------------------------
void S_113()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setDigit(0,0);
    LEDDisplay.setDigit(0,1);
    LEDDisplay.setDigit(1,2);
    LEDDisplay.setDigit(1,3);    
  }
  if (!(S1.getHiLow()== BLK && S2.getHiLow()== BLK && S3.getHiLow()== WHT && S4.getHiLow()== WHT)) FSM1.transit(S_start);   
}
//------------------------------------
void S_114()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setDigit(0,0);
    LEDDisplay.setDigit(0,1);
    LEDDisplay.setDigit(1,2);
    LEDDisplay.setDigit(0,3); 
  }
  if (!(S1.getHiLow()== BLK && S2.getHiLow()== BLK && S3.getHiLow()== WHT && S4.getHiLow()== BLK)) FSM1.transit(S_start);   
}
//------------------------------------
void S_115()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setDigit(0,0);
    LEDDisplay.setDigit(0,1);
    LEDDisplay.setDigit(0,2);
    LEDDisplay.setDigit(1,3);  
  }
  if (!(S1.getHiLow()== BLK && S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== WHT)) FSM1.transit(S_start);   
}
//------------------------------------
void S_116()   
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(0000); 
  }
  if (!(S1.getHiLow()== BLK && S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK)) FSM1.transit(S_start);   
}

