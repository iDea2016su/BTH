#include "main.h"
#include "usart.h"
#include "led.h"
#include "sys.h"
#include "adc.h"
#include "rtc.h"
#include "timer.h"


int main(void)
{
  HAL_Init();
  SystemClock_Config();
  LED_Init();
  ADC_Init();
  RTC_Init();
  TIM2_Init();
  MX_USART2_UART_Init();
	int i =0;
  while (1)
  {
    printf("hello\r\n");
		HAL_Delay(500);
		i++;
		LED(0,i%2);
		LED(1,i%2);
		LED(2,i%2);
		LED(3,i%2);
		LED(4,i%2);
  }
}