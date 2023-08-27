/**
 * @file      main_state.c
 * @author    Christian Hildenbrand
 * @date      01.05.2023
 *
 * @brief [description]
 */

/*******************************************************************************
* Includes
*******************************************************************************/

#include <stdbool.h>

#include "main.h"
#include "stm32g4xx_hal_gpio.h"

/*******************************************************************************
* Defines
*******************************************************************************/
//#define LD2_SW_TOOGLE
//#define LD2_BUTTON_POLLING
//#define LD2_BUTTON_INT_TOGGLE
#define LD2_BUTTON_INT_DOUBLE

#define LD2_SW_TOGGLE_CYCLE ((uint32_t)3500000UL)

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Static Variables
*******************************************************************************/
static uint32_t m_MainState_CycleCount = 0u;
static bool m_MainState_initialized = false;

#if defined (LD2_BUTTON_INT_TOGGLE)
bool m_Event_UserLedToogle = false;

#elif defined (LD2_BUTTON_INT_DOUBLE)
bool m_Event_UserLedOn = true;
bool m_Event_UserLedOff = false;

#endif

/*******************************************************************************
* Functions
*******************************************************************************/

void MainState_Init(void)
{
	m_MainState_initialized = true;
}

void MainState_Cyclic(void)
{
#if defined(LD2_BUTTON_POLLING)
	/* Read Pin State of User Button (Blue) */
	GPIO_PinState userButtonState =
			HAL_GPIO_ReadPin(B1_USER_BUTTON_GPIO_Port, B1_USER_BUTTON_Pin);

	if (userButtonState == GPIO_PIN_SET)
	{
		HAL_GPIO_WritePin(LD2_USER_GPIO_Port, LD2_USER_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LD2_USER_GPIO_Port, LD2_USER_Pin, GPIO_PIN_SET);
	}

#elif defined(LD2_BUTTON_INT_TOGGLE)
	if (m_Event_UserLedToogle)
	{
		HAL_GPIO_TogglePin(LD2_USER_GPIO_Port, LD2_USER_Pin);
		m_Event_UserLedToogle = false;
	}

#elif defined (LD2_BUTTON_INT_DOUBLE)

	if (m_Event_UserLedOn)
	{
		HAL_GPIO_WritePin(LD2_USER_GPIO_Port, LD2_USER_Pin, GPIO_PIN_SET);
		m_Event_UserLedOn = false;
	}
	if (m_Event_UserLedOff)
	{
		HAL_GPIO_WritePin(LD2_USER_GPIO_Port, LD2_USER_Pin, GPIO_PIN_RESET);
		m_Event_UserLedOff = false;
	}

#elif defined(LD2_SW_TOOGLE)
	if (m_MainState_CycleCount % LD2_SW_TOGGLE_CYCLE == 0u)
	{
		HAL_GPIO_TogglePin(LD2_USER_GPIO_Port, LD2_USER_Pin);
	}
#elif defined(TIM_INT_TOGGLE)

#endif

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == B1_USER_BUTTON_INT_Pin)
	{

#if defined (LD2_BUTTON_INT_TOGGLE)
		/* For single edge solution */
		m_Event_UserLedToogle = true;
#elif defined (LD2_BUTTON_INT_DOUBLE)
		/* For Rising and Falling edge solution */
		GPIO_PinState userButtonState =
				HAL_GPIO_ReadPin(B1_USER_BUTTON_INT_GPIO_Port, B1_USER_BUTTON_INT_Pin);

		if (userButtonState == GPIO_PIN_SET)
		{
			m_Event_UserLedOn = true;
		}
		else
		{
			m_Event_UserLedOff = true;
		}
#endif
	}
}

