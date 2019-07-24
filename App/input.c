#include "input.h"

void IN_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	  /*Configure GPIO pin : PC14 */
	//PF0
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

u8 getIn(void)
{
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)==SET)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}