#include "devices.h"
#include "Arduino.h"

long timer[9] = {0,0,0,0,0,0,0,0,0};
int pin[9] = {0,O1,O2,O3,O4,O5,O6,O7,O8};
void deviceInit(void)
{
  pinMode(O1,OUTPUT);
  pinMode(O2,OUTPUT);
  pinMode(O3,OUTPUT);
  pinMode(O4,OUTPUT);
  pinMode(O5,OUTPUT);
  pinMode(O6,OUTPUT);
  pinMode(O7,OUTPUT);
  pinMode(O8,OUTPUT);
  digitalWrite(O1,1);
  digitalWrite(O2,1);
  digitalWrite(O3,1);
  digitalWrite(O4,1);
  digitalWrite(O5,1);
  digitalWrite(O6,1);
  digitalWrite(O7,1);
  digitalWrite(O8,1);
  
}
void deviceSet(int pinNum, int value, long time)
{
  timer[pinNum] = time;
  digitalWrite(pin[pinNum], int(value/100));
//  Serial.println(pinNum);
}
void countdown()
{
  for (char i=1;i<=8;i++)
  {
    if (timer[i]>-1) 
    {
      timer[i]--;
      if (timer[i]==-1) digitalWrite(pin[i],!digitalRead(pin[i]));
    }
  }
}
long getTime(int outPin)
{
  if (timer[outPin] ==0) return -1;
  return timer[outPin];
}
int getPin(int outPin)
{
  return 100*(digitalRead(pin[outPin]));
}
