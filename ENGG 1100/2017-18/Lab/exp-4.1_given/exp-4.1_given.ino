/*
  ENGG1100 Experiment-4.1, Basic setup of using Arduino
  Board: Arduino Nano
  Version: 20170626_AlexSiu
*/
// the setup function runs once when you press reset or power the board
void setup() 
{
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  int a=0;
  a = digitalRead(A0);
  digitalWrite(A1, a);   // turn the LED1 on (HIGH, true or '1' is the voltage level)
}
