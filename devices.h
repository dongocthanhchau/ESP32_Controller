#ifndef _devices__h_
#define _devices__h_

#define O1 32
#define O2 33
#define O3 25
#define O4 26
#define O5 27
#define O6 13
#define O7 19
#define O8 15

void deviceInit(void);
void deviceSet(int pinNum, int value, long time);
void countdown();
long getTime(int outPin);
int getPin(int outPin);

#endif
