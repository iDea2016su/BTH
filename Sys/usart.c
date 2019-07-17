#include "usart.h"
#include "sys.h"
#include "main.h"
#include <stdio.h>


UART_HandleTypeDef huart2;


#if 1
#pragma import(__use_no_semihosting)             
             
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       

void _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{  
  HAL_HalfDuplex_EnableTransmitter(&huart2);	
	u8 p = ch;
	HAL_UART_Transmit(&huart2, &p, 1, 2000);    
	return ch;
}
#endif 



void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
	
}

//void HAL_UART_MspInit(UART_HandleTypeDef *huart)
//{
//	GPIO_InitTypeDef GPIO_Initure;
//	
//	if(huart->Instance==USART2)
//	{
//		__HAL_RCC_GPIOA_CLK_ENABLE();			 
//		__HAL_RCC_USART2_CLK_ENABLE();			   
//    GPIO_Initure.Pin = GPIO_PIN_9;
//    GPIO_Initure.Mode = GPIO_MODE_AF_OD;
//    GPIO_Initure.Pull = GPIO_PULLUP;
//    GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_Initure.Alternate = GPIO_AF4_USART2;
//    HAL_GPIO_Init(GPIOA, &GPIO_Initure);		
//	}

//}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART2)
	{

	}
}