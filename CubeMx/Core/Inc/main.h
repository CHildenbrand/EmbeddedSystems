/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define B1_USER_BUTTON_Pin GPIO_PIN_13
#define B1_USER_BUTTON_GPIO_Port GPIOC
#define ENC_QD_ORANGE_Pin GPIO_PIN_2
#define ENC_QD_ORANGE_GPIO_Port GPIOC
#define LD2_USER_Pin GPIO_PIN_5
#define LD2_USER_GPIO_Port GPIOA
#define ENC_QD_YELLOW_Pin GPIO_PIN_2
#define ENC_QD_YELLOW_GPIO_Port GPIOB
#define LED_D1_Pin GPIO_PIN_10
#define LED_D1_GPIO_Port GPIOB
#define LED_D2_Pin GPIO_PIN_7
#define LED_D2_GPIO_Port GPIOC
#define LED_D0_Pin GPIO_PIN_5
#define LED_D0_GPIO_Port GPIOB
#define LED_D3_Pin GPIO_PIN_9
#define LED_D3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
