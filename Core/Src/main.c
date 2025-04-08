/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
static dozdgirState dozdgir_status={0};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//extern char uart1_rx_buffer[RX_BUFFER_SIZE];
extern char uart1_rx_temp;
//extern char receive_message[RX_BUFFER_SIZE];
//extern char receive_message_number[30];
char number[] = "+989128442948";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
		if (huart == &huart1)
		{
				get_answer();
		}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const char matn[]="AT\n\r";

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
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(500);

	if (GSM_init())
	{
		green_blink(2000);
		printf("GSM initilized successfully.");
	}
	else
	{
		yellow_blink(2000);
		printf("GSM not initialized.");
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  switch (dozdgir_status.vaziat) {
		case amade_be_kar:

			break;
		case dozdgir_faal:

			break;
		case ajir_faal:

			break;

		case faal_kardan_dozdgir:
			enableAjir(true);
			HAL_Delay(100);
			enableAjir(false);
			dozdgir_status.vaziat=dozdgir_faal;
			break;

		case faal_kardan_ajir:
			TIM2->CNT=0;
			HAL_TIM_Base_Start_IT(&htim2);
			enableAjir(GPIO_PIN_SET);
			dozdgir_status.vaziat=ajir_faal;
//			GSM_send_message("Dozdgir Faal Shod\n\rS-Help...", number);
			GSM_send_message("062F06500632062F06AF06CC063100200631064806"\
					"340020062F064E06A90650062A0647D83DDD0A", number);
			break;
		case faal_kardan_ersal_sms:

			break;

		case khamosh_kardan_ajir:
			enableAjir(GPIO_PIN_RESET);
			HAL_TIM_Base_Stop_IT(&htim2);
			dozdgir_status.vaziat=dozdgir_faal;
			break;

		case khamosh_kardan_dozdgir:
			enableAjir(GPIO_PIN_RESET);
			dozdgir_status.vaziat=amade_be_kar;
			break;

		case ersal_sms:
			HAL_UART_Transmit_IT(&huart1, matn, sizeof(matn));
			HAL_Delay(100);
			break;

		default:
			break;
	}

//  if (strstr(uart1_rx_buffer, "+CMTI:") != NULL)
//  {
//	  GSM_read_message();
//	  if ((strstr(receive_message, "Test SMS") != NULL) && (strstr(receive_message_number, number) != NULL))
//		{
//				GSM_send_message("sms received", number);
//		}
//
//
//	  memset(receive_message, 0, RX_BUFFER_SIZE);
//	  memset(receive_message_number, 0, RECEIVE_NUMBER_SIZE);
//
//	}
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void toggleLed(void)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
void enableAjir(uint8_t state)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, state);
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == pir_int_Pin)
	{ /* Enable Ajir */

		if(dozdgir_status.vaziat==dozdgir_faal ||\
				dozdgir_status.vaziat==ajir_faal)
		{
			dozdgir_status.vaziat=faal_kardan_ajir;
		}
	}

	if (GPIO_Pin == dz_enb_Pin)
	{ /* Enable dozdgir */

		if (dozdgir_status.vaziat!=ajir_faal)
		{
			dozdgir_status.vaziat=faal_kardan_dozdgir;
		}

	}

	if (GPIO_Pin == dz_dsb_Pin)
	{ /* Disable dozdgir */

		dozdgir_status.vaziat=khamosh_kardan_dozdgir;

	}

	if (GPIO_Pin == pwr_int_Pin)
	{ //Power Loss Happened

	}
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if(htim->Instance == TIM2)
  {
	  if(dozdgir_status.vaziat==ajir_faal)
	  {
		  dozdgir_status.vaziat=khamosh_kardan_ajir;
	  }
  }
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
