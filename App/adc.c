#include "adc.h"
#include "filter.h"

ADC_HandleTypeDef hadc;

void ADC_Init(void)
{
 /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = ENABLE;
  hadc.Init.Oversample.Ratio = ADC_OVERSAMPLING_RATIO_2;
  hadc.Init.Oversample.RightBitShift = ADC_RIGHTBITSHIFT_NONE;
  hadc.Init.Oversample.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = ENABLE;
  hadc.Init.LowPowerFrequencyMode = ENABLE;
  hadc.Init.LowPowerAutoPowerOff = ENABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
//  sConfig.Channel = ADC_CHANNEL_3;
//  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
//  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_4;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

u16 getBattery()   
{
	ADC_ChannelConfTypeDef ADC1_ChanConf;
	ADC1_ChanConf.Channel=ADC_CHANNEL_4;                                  
	ADC1_ChanConf.Rank=ADC_RANK_CHANNEL_NUMBER;   	
	HAL_ADC_ConfigChannel(&hadc,&ADC1_ChanConf);        //通道配置
	HAL_ADC_Start(&hadc);                               //开启ADC
	HAL_ADC_PollForConversion(&hadc,300);                //轮询转换
	return (u16)filter((u16)HAL_ADC_GetValue(&hadc));	            //返回最近一次ADC1规则组的转换结果
	//return (u16)HAL_ADC_GetValue(&hadc);
}

u16 getMotor()   
{
//	ADC_ChannelConfTypeDef ADC1_ChanConf;
//	ADC1_ChanConf.Channel=ADC_CHANNEL_3;                                  
//	ADC1_ChanConf.Rank=ADC_RANK_CHANNEL_NUMBER;   	
//	HAL_ADC_ConfigChannel(&hadc,&ADC1_ChanConf);        //通道配置
//	HAL_ADC_Start(&hadc);                               //开启ADC
//	HAL_ADC_PollForConversion(&hadc,300);                //轮询转换
//	return (u16)HAL_ADC_GetValue(&hadc);	            //返回最近一次ADC1规则组的转换结果
	
	return 100;
}