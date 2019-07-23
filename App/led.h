#ifndef _LED_
#define _LED_

#include "sys.h"
void LED_Init(void);

void LED(u8 led,u8 status);
void ledMode(u8 s1,u8 s2, u8 s3,u8 s4);
void ledCharge(u8 s);
void BatWarn();


#endif