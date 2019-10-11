#include "key.h"
#include "led.h"
#include "timer.h"
#include "app.h"
#include "input.h"
#include "dog.h"

extern int batteryValue;
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
		HAL_Delay(10);
		int i =0;
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
		{
			while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET)
			{
				i++;
				HAL_Delay(5);
				feedDog();
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
				printf("get in %d\r\n",getIn());
			}
			else
			{
				sleep();
			}
		}
  } 
}
