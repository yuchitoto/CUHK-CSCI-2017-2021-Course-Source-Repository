
#include "ENGG1100.h"
#include <Servo.h>
#define BLK 0
#define WHT 1
#define OPN 90
#define CLS 180

  
FSMClass FSM1;          //The given FSM is named 'FSM1'.
TM1637DisplayClass LED(D10, D11); //7-segment LED Display is connected to D10,D11 for debug
ServoClass LID(D9);
/*SensorClass S1(A5); */
SensorClass L(A4); 
SensorClass R(A3); 
SensorClass C(A2); 
MotorClass MR(D3,D2);
MotorClass ML(D5,D4);
UltrasoundSensorClass Sonic(D12,D13);

int t;
int s[3] = {0};

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);          //optional, for debug
  LED.setBrightness(15); //optional
  FSM1.init(S_999);           // must have this line, you can change the first state of the FSM
  LID.init();
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
    LID.setValue(CLS);
    LED.setValue(999); 
    ML.setSpeed(0);
    MR.setSpeed(0);
    t=0;    
  }
  if (FSM1.getTime() >2000){
    if(L.getHiLow() == WHT && C.getHiLow() == BLK && R.getHiLow() == WHT) {FSM1.transit(S_100);}
    if(L.getHiLow() == BLK && C.getHiLow() == BLK && R.getHiLow() == WHT) {FSM1.transit(S_200);}
    if(L.getHiLow() == WHT && C.getHiLow() == BLK && R.getHiLow() == BLK) {FSM1.transit(S_300);}
  }
}
void S_100(){
   if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(100);
    MR.setSpeed(255);
    ML.setSpeed(255);
  }
  if(L.getHiLow()==BLK && R.getHiLow()==WHT) FSM1.transit(S_100L);
  if(R.getHiLow()==BLK && L.getHiLow()==WHT) FSM1.transit(S_100R);
  if(L.getHiLow()==BLK && R.getHiLow()==BLK && C.getHiLow()==BLK) FSM1.transit(S_101);

}

void S_100L()
{
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(0001);
    MR.setSpeed(255);
    ML.setSpeed(0);
  }
  if(!(L.getHiLow()==BLK && R.getHiLow()==WHT)) FSM1.transit(S_100);
}
void S_100R()
{
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(0002);
    MR.setSpeed(0);
    ML.setSpeed(255);
  }
  if(!(R.getHiLow()==BLK && L.getHiLow()==WHT)) FSM1.transit(S_100);
}

void S_300(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(300);
    MR.setSpeed(255);
    ML.setSpeed(255);
  }
  if(L.getHiLow()==BLK && R.getHiLow()==BLK && C.getHiLow()==BLK) FSM1.transit(S_301);
  if(L.getHiLow()==BLK && R.getHiLow()==WHT) FSM1.transit(S_300L);
  if(R.getHiLow()==BLK && L.getHiLow()==WHT) FSM1.transit(S_300R);
}
void S_300L(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(0001);
    MR.setSpeed(255);
    ML.setSpeed(0);
  }
  if(!(L.getHiLow()==BLK && R.getHiLow()==WHT)) FSM1.transit(S_300);
}
void S_300R(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(0001);
    MR.setSpeed(0);
    ML.setSpeed(255);
  }
  if(!(L.getHiLow()==WHT && R.getHiLow()==BLK)) FSM1.transit(S_300);
}
void S_301(){
  if(FSM1.doTask())
  {
    t=0;
    LID.setValue(OPN);
    LED.setValue(301);
    ML.setSpeed(0);
    MR.setSpeed(-255);
  }
  if(FSM1.getTime()>630) FSM1.transit(S_302);
}
void S_302(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(302);
    MR.setSpeed(255);
    ML.setSpeed(255);
  }
  if(R.getHiLow()==BLK && FSM1.getTime()>2000) {s[0]=FSM1.getTime();FSM1.transit(S_303);}
}
void S_303(){
  if(FSM1.doTask())
  {
    LID.setValue(CLS);
    LED.setValue(303);
    MR.setSpeed(-255);
    ML.setSpeed(-255);
  }
  if(C.getHiLow()==BLK && FSM1.getTime()>s[0] && FSM1.getTime()<s[0]+300) FSM1.transit(S_304);
}
void S_304(){
  if(FSM1.doTask())
  {
    t=0;
    LID.setValue(CLS);
    LED.setValue(301);
    ML.setSpeed(-255);
    MR.setSpeed(0);
  }
  if(FSM1.getTime()>630) FSM1.transit(S_104);
}

//-------------------------------------------------
void S_200(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(200);
    MR.setSpeed(255);
    ML.setSpeed(255);
  }
  if(L.getHiLow()==BLK && R.getHiLow()==BLK && C.getHiLow()==BLK) FSM1.transit(S_201);
  if(L.getHiLow()==BLK && R.getHiLow()==WHT) FSM1.transit(S_200L);
  if(R.getHiLow()==BLK && L.getHiLow()==WHT) FSM1.transit(S_200R);
}
void S_200L(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(0001);
    MR.setSpeed(255);
    ML.setSpeed(0);
  }
  if(!(L.getHiLow()==BLK && R.getHiLow()==WHT)) FSM1.transit(S_200);
}
void S_200R(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(0001);
    MR.setSpeed(0);
    ML.setSpeed(255);
  }
  if(!(L.getHiLow()==WHT && R.getHiLow()==BLK)) FSM1.transit(S_200);
}
void S_201(){
  if(FSM1.doTask())
  {
    t=0;
    LID.setValue(OPN);
    LED.setValue(201);
    MR.setSpeed(0);
    ML.setSpeed(-250);
  }
  if(FSM1.getTime()>600) FSM1.transit(S_202);
}
void S_202(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(202);
    MR.setSpeed(255);
    ML.setSpeed(255);
  }
  if(L.getHiLow()==BLK && FSM1.getTime()>2000) {s[0]=FSM1.getTime();FSM1.transit(S_203);}
}
void S_203(){
  if(FSM1.doTask())
  {
    LID.setValue(CLS);
    LED.setValue(203);
    MR.setSpeed(-255);
    ML.setSpeed(-250);
  }
  if(C.getHiLow()==BLK && FSM1.getTime()>s[0]-100 && FSM1.getTime()<s[0]+300) FSM1.transit(S_204);
}
void S_204(){
  if(FSM1.doTask())
  {
    t=0;
    LID.setValue(CLS);
    LED.setValue(204);
    MR.setSpeed(-250);
    ML.setSpeed(0);
  }
  if(FSM1.getTime()>600) FSM1.transit(S_104);
}

//--------------------------------------
void S_101(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(101);
    MR.setSpeed(255);
    ML.setSpeed(255);
  }
  if((L.getHiLow()==WHT && C.getHiLow()==WHT && R.getHiLow()==WHT) || Sonic.getDistance()<15) FSM1.transit(S_102);
}
//------------------------------------------
void S_102(){
  if(FSM1.doTask())
  {
    LID.setValue(CLS);
    LED.setValue(102);
    MR.setSpeed(0);
    ML.setSpeed(0);
  }
  if(FSM1.getTime()>700) FSM1.transit(S_103);
}

void S_103(){
  if(FSM1.doTask())
  {
    LID.setValue(CLS);
    LED.setValue(103);
    MR.setSpeed(-255);
    ML.setSpeed(-255);
  }
  if(L.getHiLow()==BLK && R.getHiLow()==BLK && C.getHiLow()==BLK) FSM1.transit(S_104);
}

void S_104(){
  if(FSM1.doTask())
  {
    LID.setValue(CLS);
    LED.setValue(104);
    MR.setSpeed(-255);
    ML.setSpeed(-255);
  }

  if(L.getHiLow()==WHT && C.getHiLow()==WHT && R.getHiLow()==WHT) FSM1.transit(S_105);
}



void S_105(){
  if(FSM1.doTask())
  {
    LID.setValue(CLS);
    LED.setValue(105);
    MR.setSpeed(0);
    ML.setSpeed(0);
  }
  if(FSM1.getTime()>1000) FSM1.transit(S_106);
  
}

void S_106(){
  if(FSM1.doTask())
  {
    LID.setValue(OPN);
    LED.setValue(106);
    MR.setSpeed(0);
    ML.setSpeed(0);
  }
}

