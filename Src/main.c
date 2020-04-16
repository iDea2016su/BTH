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
void EnterStop();
int mspeed;

int firstWeakUp = 0;
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
	printf("sys start11111111111111111111111111111111111111111111111111111111\r\n");
	delay(1000);
	EnterStop();
  while (1)
  {
		inCount ++;
		if(inCount%9==0)
	  mspeed = getMotor();
	  delay(50);
		charge = getIn();
		int status = getOnOff();		
		if(inCount%9==0)
		{
			//printf("Bat %d in %d\r\n",getBatStaus(),charge);
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
		
		delay(50);
		Tick();
    long time = inCount;
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
			EnterStop();
		}
		printf("inCount:%d\r\n",time);
  }
}

void EnterStop()
{
	printf("enter stop\r\n");
	SysTick->CTRL = 0x00;//close tick
  SysTick->VAL = 0x00;// clear tick
  
  HAL_PWREx_EnableUltraLowPower();
  HAL_PWREx_EnableFastWakeUp();
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
	
	GPIO_InitTypeDef GPIO_InitStructure;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStructure.Pin = GPIO_PIN_All;
  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  //HAL_GPIO_Init(GPIOA, &GPIO_InitStructure); 
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
  //__HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();
	__HAL_RCC_TIM2_CLK_DISABLE();	
	//congfig weakup pin
	KEY_Init();
  //enter STOP without RTC
	firstWeakUp = 0;
	inCount = 0;
	clearTick();
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	//weak up
	
}