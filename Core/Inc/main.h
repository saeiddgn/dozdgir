/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "stdbool.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
enum vaziat
{
	amade_be_kar=0,
	dozdgir_faal,
	ajir_faal,
	faal_kardan_dozdgir,
	khamosh_kardan_dozdgir,
	faal_kardan_ajir,
	khamosh_kardan_ajir,
	faal_kardan_ersal_sms,
	ersal_sms
};

typedef struct
{
	uint8_t	dozdgir:1;
	uint8_t	ajir:1;
	uint8_t vaziat;


}dozdgirState;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define pwr_int_Pin GPIO_PIN_0
#define pwr_int_GPIO_Port GPIOA
#define pwr_int_EXTI_IRQn EXTI0_IRQn
#define pir_int_Pin GPIO_PIN_1
#define pir_int_GPIO_Port GPIOB
#define pir_int_EXTI_IRQn EXTI1_IRQn
#define dz_enb_Pin GPIO_PIN_12
#define dz_enb_GPIO_Port GPIOB
#define dz_enb_EXTI_IRQn EXTI15_10_IRQn
#define dz_dsb_Pin GPIO_PIN_15
#define dz_dsb_GPIO_Port GPIOB
#define dz_dsb_EXTI_IRQn EXTI15_10_IRQn

/* USER CODE BEGIN Private defines */
void toggleLed(void);
void enableAjir(uint8_t state);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
