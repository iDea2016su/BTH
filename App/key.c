#include "key.h"
#include "led.h"
#include "app.h"
#include "usart.h"
#include "adc.h"
#include "rtc.h"
#include "timer.h"
#include "input.h"
#include "sys.h"

extern int batteryValue;
extern int firstWeakUp;
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_0)
  {

		int i =0;
		if(firstWeakUp==0)
		{
			firstWeakUp = 1;
			HAL_Init();
      SystemClock_Config();
      LED_Init();
      ADC_Init();
      //MX_USART2_UART_Init();
	    TIM2_Init(4800,200);
	    //KEY_Init();
	    IN_Init();
	    printf("weakup\r\n");
		}
		delay(10);
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
		{
			while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
			{
				i++;
				delay(5);
				if(i>=100)
				{
					break;
				}
				//printf("%d\r\n",i);
			}
			if(i<100)
			{
				if(getIn()==0)
				{
					modeChange();
				}
				//printf("get in %d\r\n",getIn());
			}
			else
			{
				sleep();
			}
		}
  } 
}
