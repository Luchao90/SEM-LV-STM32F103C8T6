/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define HEARTBEAT_TIME  250
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* Definitions for heartbeat */
osThreadId_t heartbeatHandle;
const osThreadAttr_t heartbeat_attributes = {
  .name = "heartbeat",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */

osThreadId_t semaphoreHandle;
const osThreadAttr_t semaphore_attributes = {
  .name = "semaphore",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
void heartbeatTask(void *argument);

/* USER CODE BEGIN PFP */

void semaphoreTask(void *argument);

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of heartbeat */
  heartbeatHandle = osThreadNew(heartbeatTask, NULL, &heartbeat_attributes);

  /* USER CODE BEGIN RTOS_THREADS */

  semaphoreHandle = osThreadNew(semaphoreTask, NULL, &semaphore_attributes);

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LIGHT_RED_Pin|LIGHT_YELLOW_Pin|LIGHT_GREEN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LIGHT_RED_Pin LIGHT_YELLOW_Pin LIGHT_GREEN_Pin */
  GPIO_InitStruct.Pin = LIGHT_RED_Pin|LIGHT_YELLOW_Pin|LIGHT_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

#define TIME_DEFAULT_STEP_1   3000
#define TIME_DEFAULT_STEP_2   500
#define TIME_DEFAULT_STEP_3   2000
#define TIME_DEFAULT_STEP_4   1000
#define TIME_SEQUENCE_ALERT   500
#define TIME_STARTUP_TEST     500

typedef enum {
  SEQUENCE_ALERT,
  SEQUENCE_NORMAL,
  SEQUENCE_QTY
} semaphore_sequences_t;

semaphore_sequences_t sequence_selected = SEQUENCE_ALERT;

void semaphoreTask(void *argument)
{
  /* Startup sequence */
  HAL_GPIO_WritePin(LIGHT_RED_GPIO_Port, LIGHT_RED_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LIGHT_YELLOW_GPIO_Port, LIGHT_YELLOW_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LIGHT_GREEN_GPIO_Port, LIGHT_GREEN_Pin, GPIO_PIN_SET);
  osDelay(TIME_STARTUP_TEST);

  HAL_GPIO_WritePin(LIGHT_RED_GPIO_Port, LIGHT_RED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LIGHT_YELLOW_GPIO_Port, LIGHT_YELLOW_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LIGHT_GREEN_GPIO_Port, LIGHT_GREEN_Pin, GPIO_PIN_SET);
  osDelay(TIME_STARTUP_TEST);

  HAL_GPIO_WritePin(LIGHT_RED_GPIO_Port, LIGHT_RED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LIGHT_YELLOW_GPIO_Port, LIGHT_YELLOW_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LIGHT_GREEN_GPIO_Port, LIGHT_GREEN_Pin, GPIO_PIN_RESET);
  osDelay(TIME_STARTUP_TEST);

  while(1)
  {

    switch (sequence_selected)
    {
    case SEQUENCE_ALERT:
      HAL_GPIO_TogglePin(LIGHT_RED_GPIO_Port, LIGHT_RED_Pin);
      HAL_GPIO_WritePin(LIGHT_YELLOW_GPIO_Port, LIGHT_YELLOW_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LIGHT_GREEN_GPIO_Port, LIGHT_GREEN_Pin, GPIO_PIN_SET);
      osDelay(TIME_SEQUENCE_ALERT);
      break;

    case SEQUENCE_NORMAL:
      /* Step 1 */
      HAL_GPIO_WritePin(LIGHT_RED_GPIO_Port, LIGHT_RED_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LIGHT_YELLOW_GPIO_Port, LIGHT_YELLOW_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LIGHT_GREEN_GPIO_Port, LIGHT_GREEN_Pin, GPIO_PIN_SET);
      osDelay(TIME_DEFAULT_STEP_1);

      /* Step 2 */
      HAL_GPIO_WritePin(LIGHT_RED_GPIO_Port, LIGHT_RED_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LIGHT_YELLOW_GPIO_Port, LIGHT_YELLOW_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LIGHT_GREEN_GPIO_Port, LIGHT_GREEN_Pin, GPIO_PIN_SET);
      osDelay(TIME_DEFAULT_STEP_2);

      /* Step 3 */
      HAL_GPIO_WritePin(LIGHT_RED_GPIO_Port, LIGHT_RED_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LIGHT_YELLOW_GPIO_Port, LIGHT_YELLOW_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LIGHT_GREEN_GPIO_Port, LIGHT_GREEN_Pin, GPIO_PIN_RESET);
      osDelay(TIME_DEFAULT_STEP_3);

      /* Step 4 */
      HAL_GPIO_WritePin(LIGHT_RED_GPIO_Port, LIGHT_RED_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LIGHT_YELLOW_GPIO_Port, LIGHT_YELLOW_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LIGHT_GREEN_GPIO_Port, LIGHT_GREEN_Pin, GPIO_PIN_SET);
      osDelay(TIME_DEFAULT_STEP_4);
      break;
    
    default:
      osDelay(TIME_SEQUENCE_ALERT);
      break;
    }
  }
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_heartbeatTask */
/**
  * @brief  Function implementing the heartbeat thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_heartbeatTask */
void heartbeatTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    osDelay(HEARTBEAT_TIME);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
