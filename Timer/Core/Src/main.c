/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

const int MAX_LED=4;
static int index_led=0;
static int led_buffer[4]={7,5,1,2};
static int hour=15, minutes=8, second=50;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
void display7SEG(int num);
void update7SEG(int index);
void updateClockBuffer();
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG(int num) {
	//0: a, b, c ,d ,e, f=0, g=1
	if (num==0) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_SET);
	}
	//1:b, c=1, others=0
	else if (num==1) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_SET);
	}
	//2:a,b,d,e,g=0, others=1
	else if (num==2) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_RESET);
	}
	//3:a,b,c,d,g=0, others=1
	else if (num==3) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_RESET);
	}
	//4:b,c,f,g=0, others=1
	else if (num==4) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_RESET);
	}
	//5:a, c, d, f ,g=0, others=1
	else if (num==5) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_RESET);
	}
	//6:a, c, d , e, f, g=0, others=1
	else if (num==6) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_RESET);
	}
	//7:a,b,c=0, others=1
	else if (num==7) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_SET);
	}
	//8:all=0
	else if (num==8) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_RESET);
	}
	//9: e=1, others=0
	else if (num==9) {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_RESET);
	}
	//else: set all
	else {
		HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, GPIO_PIN_SET);
	}
}

void update7SEG(int index) {
	switch (index) {
		case 0:
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			display7SEG(led_buffer[0]);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
			break;

		case 1:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			display7SEG(led_buffer[1]);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
			break;

		case 2:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			display7SEG(led_buffer[2]);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
			break;

		case 3:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			display7SEG(led_buffer[3]);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}

void updateClockBuffer() {
	led_buffer[0]=hour/10;
	led_buffer[1]=hour%10;
	led_buffer[2]=minutes/10;
	led_buffer[3]=minutes%10;
}
int timer0_counter=0;
int timer0_flag=0;
int timer1_counter=0;
int timer1_flag=0;
int TIMER_CYCLE=10;
void setTimer0(int duration) {
	timer0_counter=duration/TIMER_CYCLE;
	timer0_flag=0;
}
void timer_run() {
	if (timer0_counter>0) {
		timer0_counter--;
		if (timer0_counter==0) timer0_flag=1;
	}
	if (timer1_counter>0) {
			timer1_counter--;
			if (timer1_counter==0) timer1_flag=1;
	}
}

void setTimer1(int duration) {
	timer1_counter=duration/TIMER_CYCLE;
	timer1_flag=0;
}

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
  MX_TIM2_Init();
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setTimer0(910);
  setTimer1(970);
  while (1)
  {
	  if (timer0_flag==1) {
		second++;
		if (second>=60) {
			second=0;
			minutes++;
		}
		if (minutes>=60) {
			minutes=0;
			hour++;
		}
		if (hour>=24) {
			hour=0;
		}
		updateClockBuffer();
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		setTimer0(1000);
	  }
	  if (timer1_flag==1) {
		  index_led--;
		  if (index_led<0) index_led=3;
		  update7SEG(index_led);
		  setTimer1(250);
	  }
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ) {
	timer_run();
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
