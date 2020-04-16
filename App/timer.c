#include "timer.h"

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim21;
TIM_OC_InitTypeDef TIM2_CH2Handler;      

void TIM2_Init(u16 psc,u16 arr)
{
   /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */
	
	    GPIO_InitTypeDef GPIO_Initure;
	  __HAL_RCC_TIM2_CLK_ENABLE();			 
    __HAL_RCC_GPIOA_CLK_ENABLE();			 
	
    GPIO_Initure.Pin=GPIO_PIN_1;          
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	   
    GPIO_Initure.Pull=GPIO_PULLUP;         
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     
	  GPIO_Initure.Alternate=GPIO_AF2_TIM2;	 
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 23;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);  
  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);
	TIM_Set(0);
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
void TIM_Set(u32 compare)
{
    TIM2->CCR2=compare;
    //HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);  
	
} 

void MX_TIM21_Init(void)
{

  /* USER CODE BEGIN TIM21_Init 0 */

  /* USER CODE END TIM21_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM21_Init 1 */

  /* USER CODE END TIM21_Init 1 */
  htim21.Instance = TIM21;
  htim21.Init.Prescaler = 2399;
  htim21.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim21.Init.Period = 4999;
  htim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim21.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim21) != HAL_OK)
  {
    Error_Handler();

  /* USER CODE END TIM21_Init 2 */
	}
	HAL_TIM_Base_Start_IT(&htim21);
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim21);
}

//定时器3中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&htim21))
    {
        //printf("timer\r\n");
    }
}