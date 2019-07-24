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

#define BatLow 1000
#define MotoHigh 1000
#define Dura 500
#define CloseTime (1000/Dura)*60*2

#define P1S (1000/Dura)*30
#define P1D (1000/Dura)*31

#define P2S (1000/Dura)*60
#define P2D (1000/Dura)*61

#define P3S (1000/Dura)*90
#define P3D (1000/Dura)*91

#define P4S (1000/Dura)*120
#define P4D (1000/Dura)*121


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
  while (1)
  {
		printf("Bta %d\r\n",getBattery());
		if((getIn() == 0))
		{
			BatWarn();
		}
		else if(getIn()==1)
		{
			ledCharge(1);
			sleep();
		}
		else
		{
			ledCharge(0);
		}
		
//		if(getMotor()>MotoHigh)
//		{
//			//sleep();
//		}
		HAL_Delay(Dura);
		Tick();
    long time = getTick();
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
		if(time>P4S)
		{
			sleep();
		}
		
  }
}