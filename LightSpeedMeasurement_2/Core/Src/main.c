/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stm32f4xx.h>

/* Se incluyen las librerías para el manejo de variables */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Se incluyen los drivers de los periféricos a utilizar */
#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"
#include "PwmDriver.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim5;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
GPIO_Handler_t 		handlerStateLED 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};

BTIMER_Handler_t	handlerLightTimer		= {0};

EXTI_Config_t		extiEmision				= {0}; 		// Para configurar el EXTI
EXTI_Config_t		extiReception			= {0};

PWM_Handler_t 		handlerPWM 							= {0};
GPIO_Handler_t		handlerPwmPin						= {0};

uint32_t		timeStamp = 0;
char			bufferData[20] = {0};
uint8_t		delayFlag = 0;
uint8_t		measFlag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM5_Init(void);
/* USER CODE BEGIN PFP */
void initSystem(void);
void send_uart2 (char *string);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
  initSystem();
  HAL_TIM_Base_Start(&htim5);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  if(delayFlag){
//		  HAL_Delay(1000);
//		  delayFlag = 0;
//	  }

//	  if (~HAL_GPIO_ReadPin(LASER_GPIO_Port, LASER_Pin)){
//		  HAL_Delay(500);
//		  measFlag = 1;
//		  __NVIC_EnableIRQ(EXTI15_10_IRQn);
//		  HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, 1);
//		  __HAL_TIM_SET_COUNTER(&htim5, 0);
//	  }
	  HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, 1);

	  HAL_Delay(100);

	  HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, 0);

	  HAL_Delay(500);




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 2-1;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 4294967295;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LASER_Pin */
  GPIO_InitStruct.Pin = LASER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(LASER_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


void initSystem(void){

	/* Configuración del State LED */
	handlerStateLED.pGPIOx 								= GPIOA;
	handlerStateLED.GPIO_PinConfig.GPIO_PinNumber		= PIN_5;
	handlerStateLED.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerStateLED.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerStateLED.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	// Se carga la configuración del State LED
	GPIO_Config(&handlerStateLED);

	/* Configuración del Timer2, que controla el blinky del StateLED */
	handlerStateLedTimer.ptrTIMx					= TIM3;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed	= TIMER_INCR_SPEED_100us;
	handlerStateLedTimer.timerConfig.Timer_period	= 2500;
	// Se carga la configuración del Timer2
	BTimer_Config(&handlerStateLedTimer);

	/* Configuración del EXTI10 */
	extiEmision.EXTIx			= EXTI10;
	extiEmision.pinPort			= PC;
	extiEmision.pinPUPD_Mode    = GPIO_PUPDR_PULLDOWN;
	extiEmision.triggerMode		= RISING_TRIGGER;
	// Se carga la configuración del EXTI
	exti_Config(&extiEmision);

	/* Configuración del EXTI10 */
	extiReception.EXTIx			= EXTI9;
	extiReception.pinPort		= PA;
	extiReception.pinPUPD_Mode  = GPIO_PUPDR_PULLDOWN;
	extiReception.triggerMode	= RISING_TRIGGER;
	// Se carga la configuración del EXTI
//	exti_Config(&extiReception);

	/* Configuración del Pin por el que se tomará el PWM para el servomotor */
	handlerPwmPin.pGPIOx 								= GPIOB;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_7;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_HIGH;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF2;
	// Se carga la configuración del Pin para el PWM
//	GPIO_Config(&handlerPwmPin);

	/* Configuración del Timer 3 para el PWM */
	handlerPWM.ptrTIMx 					= TIM4;
	handlerPWM.pwmConfig.PWM_channel 	= CHANNEL2;
	handlerPWM.pwmConfig.PWM_prescaler	= TIMER_INCR_SPEED_100us;
	handlerPWM.pwmConfig.PWM_period		= 4000;
	handlerPWM.pwmConfig.PWM_dutyCycle	= 2000;
	// Se carga la configuración del PWM
//	PWM_Config(&handlerPWM);
}

/* Implementacion del Callback para el timer2 */
void BTimer3_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

/* Implementación del Callback para el EXTI10 */
void Exti10_Callback(void){
	timeStamp = htim5.Instance->CNT;
	if(measFlag){
		sprintf(bufferData,"Time = %lu ns\n", timeStamp-950);
		send_uart2(bufferData);
		delayFlag = 1;
		HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, 0);
		measFlag = 0;
		__NVIC_DisableIRQ(EXTI15_10_IRQn);
	}

}

/* Implementación del Callback para el EXTI10 */
void Exti9_Callback(void){
	sprintf(bufferData,"Time = %lf ns\n", ((double) htim5.Instance->CNT - timeStamp)*10.0);
	send_uart2(bufferData);
}

void send_uart2 (char *string)
{
	uint16_t len = strlen (string);
	HAL_UART_Transmit(&huart2, (uint8_t *) string, len, HAL_MAX_DELAY);  // transmit in blocking mode
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
