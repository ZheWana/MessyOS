/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : mf_config.c
  * @brief          : MCU FUNCTION CONFIG
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 FMSH.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by FMSH under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "mf_config.h"
#include "fm33le0xx_fl.h"

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  UART0 Initialization function
  * @param  void
  * @retval None
  */
void MF_UART0_Init(void)
{

    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_UART_InitTypeDef    defaultInitStruct;

    GPIO_InitStruct.pin        = FL_GPIO_PIN_3;
    GPIO_InitStruct.mode       = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull       = FL_DISABLE;
    GPIO_InitStruct.remapPin   = FL_DISABLE;

    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    defaultInitStruct.clockSrc          = FL_RCC_UART0_CLK_SOURCE_APB1CLK;
    defaultInitStruct.baudRate          = 115200;
    defaultInitStruct.dataWidth         = FL_UART_DATA_WIDTH_8B;
    defaultInitStruct.stopBits          = FL_UART_STOP_BIT_WIDTH_1B;
    defaultInitStruct.parity            = FL_UART_PARITY_EVEN;
    defaultInitStruct.transferDirection = FL_UART_DIRECTION_NONE;

    FL_UART_Init(UART0, &defaultInitStruct);


}

/**
  * @brief  DMA_Channel2 Initialization function
  * @param  void
  * @retval None
  */
void MF_DMA_Channel2_Init(void)
{

    /*IO CONFIG*/
    FL_DMA_InitTypeDef    defaultInitStruct;

    defaultInitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION2;
    defaultInitStruct.direction = FL_DMA_DIR_RAM_TO_PERIPHERAL;
    defaultInitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;
    defaultInitStruct.flashAddressIncMode = FL_DMA_CH7_FLASH_INC_MODE_INCREASE;
    defaultInitStruct.dataSize = FL_DMA_BANDWIDTH_8B;
    defaultInitStruct.priority = FL_DMA_PRIORITY_HIGH;
    defaultInitStruct.circMode = FL_DISABLE;

    FL_DMA_Init(DMA, &defaultInitStruct, FL_DMA_CHANNEL_2);

    FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_2);  //清通道传输完成标志
    FL_DMA_EnableIT_TransferComplete(DMA, FL_DMA_CHANNEL_2);   //使能通道传输完成中断


}
/**
  * @brief  NVIC Initialization function
  * @param  void
  * @retval None
  */
void MF_NVIC_Init(void)
{


    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    InterruptConfigStruct.preemptPriority = 1;
    FL_NVIC_Init(&InterruptConfigStruct, DMA_IRQn);


}
/**
  * @brief  The application entry point.
  * @retval int
  */
void MF_Clock_Init(void)
{
    /* MCU Configuration--------------------------------------------------------*/
    FL_RCC_EnableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_RTC);
    FL_RTC_WriteAdjustValue(RTC, 0);
    FL_RCC_DisableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_RTC);
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

    /* System interrupt init*/

    /* Initialize all configured peripherals */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void MF_SystemClock_Config(void)
{

}

void MF_Config_Init(void)
{
    /*FUNCTION CALL*/
    MF_UART0_Init();
    MF_DMA_Channel2_Init();
    MF_NVIC_Init();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN Assert_Failed */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END Assert_Failed */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
