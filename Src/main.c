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
	int i =0;
	TIM_Set(500);
  while (1)
  {
    printf("Battery %d  %d, %d\r\n",getMotor(),getBattery(),getIn());
		//printf("Moto %d\r\n",getMotor());
		HAL_Delay(500);
		i++;
		LED(0,i%2);
		LED(1,i%2);
		LED(2,i%2);
		LED(3,i%2);
		LED(4,i%2);
  }
}