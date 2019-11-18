#include "main.h"
#include "usart.h"
#include "led.h"
#include "sys.h"
#include "adc.h"
#include "rtc.h"
#include "timer.h"
#include "key.h"
#include "adc.h"
#include "input.h"
#include "app.h"
#include "dog.h"


#define MotoHigh 1000
#define Dura 500
#define CloseTime (1000/Dura)*60*2

#define P1S (1000/Dura)*29*5
#define P1D (1000/Dura)*30*5

#define P2S (1000/Dura)*59*5
#define P2D (1000/Dura)*60*5

#define P3S (1000/Dura)*89*5
#define P3D (1000/Dura)*90*5

#define P4S (1000/Dura)*119*5
#define P4D (1000/Dura)*120*5

int batteryValue = 8000;
volatile int charge;
long inCount = 0;
int mspeed;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  LED_Init();
  ADC_Init();
  MX_USART2_UART_Init();
	TIM2_Init(4800,200);
	KEY_Init();
	IN_Init();
	//@__HAL_RCC_PWR_CLK_ENABLE();
 
	//printf("sys start11111111111111111111111111111111111111111111111111111111\r\n");
	feedDog();
	MX_IWDG_Init();
	//MX_TIM21_Init();   `	
  while (1)
  {
		inCount ++;
		feedDog();
		if(inCount%9==0)
	  mspeed = getMotor();
	  HAL_Delay(50);
		charge = getIn();
		int status = getOnOff();		
		//printf("Bat %d in %d\r\n",batteryValue,charge);
		if(inCount%9==0)
		{
			if((charge == 0)&&getBatStaus())
			{
				if(status==0)
				{
					BatWarn();
				}
			}
	  }
	  if(charge==1)
		{
			sleep();
		}
		if(checkMoto(mspeed))
		{
			sleep();
		}
		
		HAL_Delay(50);
		Tick();
    long time = getTick();
		if(status == 0)
		{
			if(ifMode4()==0)
			{
				if((time>=P1S)&&(time<=P1D))
				{
					appPause();
				}
				else if((time>=P1D)&&(time<=P2S))
				{
					appContuine();
				}
				else if((time>=P2S)&&(time<=P2D))
				{
					appPause();
				}
				else if((time>=P2D)&&(time<=P3S))
				{
					appContuine();
				}
				else if((time>=P3S)&&(time<=P3D))
				{
					appPause();
				}
				else if((time>=P3D)&&(time<=P4S))
				{
					appContuine();
				} 
			}
			if((getOnOff()==0)&&(ifMode4()==1)&&(time<P4S))
			{
				//printf("mode 4 time %d\r\n",(int)time);
				if(time%20==5||time%20==10||time%20==15||time%20==0)
				{
					appPause();
				}
				else
				{
					appContuine();
				}
			}
	  }
		if(getOnOff()==1)
		{
			sleep();
		}
		if(time>P4S)
		{
			sleep();
		}
  }
}