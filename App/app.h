#ifndef APP_H
#define APP_H
#include "sys.h"


#define BatLow 3900

void modeChange();
void appPause();
void appContuine();
void Tick();
long getTick();
void clearTick();
void sleep();
u8 ifMode4();
u8 getOnOff();
u8 checkMoto(int v);
#endif