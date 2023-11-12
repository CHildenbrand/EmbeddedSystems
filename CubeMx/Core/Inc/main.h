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
#define RGB_LED_R_Pin GPIO_PIN_1
#define RGB_LED_R_GPIO_Port GPIOB
#define ENC_QD_YELLOW_Pin GPIO_PIN_2
#define ENC_QD_YELLOW_GPIO_Port GPIOB
#define LED_D1_Pin GPIO_PIN_10
#define LED_D1_GPIO_Port GPIOB
#define JOYSTICK_Y_Pin GPIO_PIN_12
#define JOYSTICK_Y_GPIO_Port GPIOB
#define JOYSTICK_X_Pin GPIO_PIN_13
#define JOYSTICK_X_GPIO_Port GPIOB
#define SERVO_PWM_Pin GPIO_PIN_14
#define SERVO_PWM_GPIO_Port GPIOB
#define RGB_LED_G_Pin GPIO_PIN_6
#define RGB_LED_G_GPIO_Port GPIOC
#define LED_D2_Pin GPIO_PIN_7
#define LED_D2_GPIO_Port GPIOC
#define RGB_LED_B_Pin GPIO_PIN_8
#define RGB_LED_B_GPIO_Port GPIOC
#define SW_1_EXTI3_Pin GPIO_PIN_3
#define SW_1_EXTI3_GPIO_Port GPIOB
#define SW_1_EXTI3_EXTI_IRQn EXTI3_IRQn
#define LED_D0_Pin GPIO_PIN_5
#define LED_D0_GPIO_Port GPIOB
#define LD4_PWM_Pin GPIO_PIN_8
#define LD4_PWM_GPIO_Port GPIOB
#define LED_D3_Pin GPIO_PIN_9
#define LED_D3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
