#include "timer.h"

TIM_HandleTypeDef TIM2_Handler; 
TIM_OC_InitTypeDef TIM2_CH2Handler;      

void TIM2_Init(u32 psc,u32 arr)
{
    TIM2_Handler.Instance=TIM2;             
    TIM2_Handler.Init.Prescaler=psc;       
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; 
    TIM2_Handler.Init.Period=arr;          
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM2_Handler);   
    HAL_TIM_PWM_MspInit(&TIM2_Handler); 	
    
    TIM2_CH2Handler.OCMode=TIM_OCMODE_PWM1;  
    TIM2_CH2Handler.Pulse=arr/2;            
                                           
    TIM2_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW;  
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH2Handler,TIM_CHANNEL_2); 
    HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_2); 

}


void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
	  __HAL_RCC_TIM2_CLK_ENABLE();			 
    __HAL_RCC_GPIOA_CLK_ENABLE();			 
	
    GPIO_Initure.Pin=GPIO_PIN_1;          
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	   
    GPIO_Initure.Pull=GPIO_PULLUP;         
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     
	  GPIO_Initure.Alternate=GPIO_AF2_TIM2;	 
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
} 

//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
//{
//    if(htim->Instance==TIM2)
//	{
//		__HAL_RCC_TIM2_CLK_ENABLE();            
//		HAL_NVIC_SetPriority(TIM2_IRQn,1,3);   
//		HAL_NVIC_EnableIRQ(TIM2_IRQn);         
//	}  
//}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM2_Handler))
    {
      //  LED1_Toggle;       
    }
}
void TIM_Set(u32 compare)
{
    TIM2->CCR2=compare; 
} 