#include "app.h"
#include "timer.h"
#include "led.h"
#include "adc.h"
#include "main.h"


#define PM1 750
#define PM2 860
#define PM3 998
#define PM4 998
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
u8 ifSleep = 1;

void modeChange()
{
	if(ifRun)
	{
		modeCount++;
		if(getBatStaus()==1)
		{
			switch(modeCount%4)
			{
				case 0: appState = APP_MODE1;ledMode(1,0,0,0);TIM_Set(PMP);break;
				case 1: appState = APP_MODE2;ledMode(0,1,0,0);TIM_Set(PMP);break;
				case 2: appState = APP_MODE3;ledMode(0,0,1,0);TIM_Set(PMP);break;
				case 3: appState = APP_MODE4;ledMode(0,0,0,1);TIM_Set(PMP);break;
				default:break;
			}
		}
		else if(getBatStaus()==0)
		{
			switch(modeCount%4)
			{
				case 0: appState = APP_MODE1;ledMode(1,0,0,0);TIM_Set(PM1/20);delay(10);TIM_Set(PM1/10);delay(20);TIM_Set(PM1/5);delay(5);TIM_Set(PM1/2);delay(5);TIM_Set(PM1);break;
				case 1: appState = APP_MODE2;ledMode(0,1,0,0);TIM_Set(PM2/20);delay(10);TIM_Set(PM2/10);delay(20);TIM_Set(PM2/5);delay(5);TIM_Set(PM2/2);delay(5);TIM_Set(PM2);break;
				case 2: appState = APP_MODE3;ledMode(0,0,1,0);TIM_Set(PM3/20);delay(10);TIM_Set(PM3/10);delay(20);TIM_Set(PM3/5);delay(5);TIM_Set(PM3/2);delay(5);TIM_Set(PM3);break;
				case 3: appState = APP_MODE4;ledMode(0,0,0,1);TIM_Set(PM4/20);delay(10);TIM_Set(PM4/10);delay(20);TIM_Set(PM4/5);delay(5);TIM_Set(PM4/2);delay(5);TIM_Set(PM4);break;
				default:break;
			}
		}
	}
	else 
	{
		ifRun = 1;
		appContuine();
	}
	ifSleep = 0;
	clearTick();
	printf("change mode\r\n");
	delay(200);
}

void appPause()
{
	ifPause = 1;
	ifSleep = 0;
	TIM_Set(PMP);
	//printf("pause\r\n");
}
void appContuine()
{
	if(getBatStaus()==0)
	{
		switch(modeCount%4)
		{
			case 0: ledMode(1,0,0,0);TIM_Set(PM1);break;
			case 1: ledMode(0,1,0,0);TIM_Set(PM2);break;
			case 2: ledMode(0,0,1,0);TIM_Set(PM3);break;
			case 3: ledMode(0,0,0,1);TIM_Set(PM4);break;
			default:break;
		}
	}
	else if(getBatStaus()==1)
	{
		switch(modeCount%4)
		{
			case 0: ledMode(1,0,0,0);TIM_Set(PMP);break;
			case 1: ledMode(0,1,0,0);TIM_Set(PMP);break;
			case 2: ledMode(0,0,1,0);TIM_Set(PMP);break;
			case 3: ledMode(0,0,0,1);TIM_Set(PMP);break;
			default:break;
		}
	}
	ifSleep = 0;
}
void Tick()
{
	if(ifSleep==0)
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
	ledChargeOff();
	//printf("sleep\r\n");
	ifSleep = 1;
	//EnterStop();
}
u8 ifMode4()
{
	if(appState == APP_MODE4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
u8 getOnOff()
{
	return ifSleep;
}
u8 checkMoto(int v)
{
	u8 s = 0;
	switch(modeCount%4)
	{
		case 0: if(v>550&&v<3000)s = 1;break;
		case 1: if(v>600&&v<3000)s = 1;break;
		case 2: if(v>600&&v<3000)s = 1;break;
		case 3: if(v>600&&v<3000)s = 1;break;
		default:break;
	}
	return s;
}

//0:ok
//1:no power
static int powerStatus = 0;
int temp = 0;
int getBatStaus()
{
	if(getOnOff())
	{
	 temp = getBattery();
	 printf("%d\r\n",temp);
	 if(temp<BatLow&&temp>2500)
	 {
		 powerStatus = 0;
		 return 0;
	 }
	 else
	 {
		 powerStatus = 1;
		 return 1;
	 }
	}else if(powerStatus == 0)
	{
		return 0;
	}
	else
	return 1;
}