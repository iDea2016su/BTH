#include "app.h"
#include "timer.h"
#include "led.h"


#define PM1 800
#define PM2 600
#define PM3 500
#define PM4 400
#define PMP 0


typedef enum
{
	APP_IDLE,
	APP_MODE1,
	APP_MODE2,
	APP_MODE3,
	APP_MODE4,
	APP_PAUSE,
	APP_SLEEP,
}AppState;

AppState appState = APP_MODE1;
int modeCount = 0;
u8 ifPause = 0;
u8 ifRun   = 0;
long sysTick = 0;


void modeChange()
{
	if(ifRun)
	{
		modeCount++;
		switch(modeCount%4)
		{
			case 0: appState = APP_MODE1;TIM_Set(PM1);ledMode(1,0,0,0);break;
			case 1: appState = APP_MODE2;TIM_Set(PM2);ledMode(0,1,0,0);break;
			case 2: appState = APP_MODE3;TIM_Set(PM3);ledMode(0,0,1,0);break;
			case 3: appState = APP_MODE4;TIM_Set(PM4);ledMode(0,0,0,1);break;
			default:break;
		}
	}
	else 
	{
		ifRun = 1;
		appContuine();
	}
	clearTick();
}

void appPause()
{
	ifPause = 1;
	TIM_Set(PMP);
}
void appContuine()
{
	switch(modeCount%4)
	{
		case 0: TIM_Set(PM1);break;
		case 1: TIM_Set(PM2);break;
		case 2: TIM_Set(PM3);break;
		case 3: TIM_Set(PM4);break;
		default:break;
	}
}
void Tick()
{
	sysTick++;
}
long getTick()
{
	return sysTick;
}
void clearTick()
{
	sysTick = 0;
}
void sleep()
{
	ifPause = 1;
	ifRun = 0;
	TIM_Set(PMP);
	ledMode(0,0,0,0);
}