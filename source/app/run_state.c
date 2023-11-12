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

#include "run_state.h"

#include "tim.h"
#include "adc.h"
#include "stm32g4xx_ll_tim.h"

/*******************************************************************************
* Defines
*******************************************************************************/

/*! Maximum Value of a 12-bit ADC channel */
#define UINT12_MAX_VALUE 0xFFFUL

/*! Conversion factor to obtain percent out of normalized value */
#define VALUE_TO_PERCENT 100UL

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

static bool RunState_Cyclic_SelfTest(RunState const* pRunState, bool* pError)
{
    bool finished = false;

    DrvCrc_Cyclic(pRunState->pCfg->pDrvCrc);

    if (DrvCrc_GetState(pRunState->pCfg->pDrvCrc) == DrvCrcState_Finished)
    {

        if (DrvCrc_IsValid(pRunState->pCfg->pDrvCrc) != false)
        {
            DrvBlinky_SetState(pRunState->pCfg->pDrvBlinky, DrvBlinkyState_Blinky);
        }

        else
        {
            DrvBlinky_SetState(pRunState->pCfg->pDrvBlinky, DrvBlinkyState_On);
        }

        finished = true;
    }

    DrvBlinky_Cyclic(pRunState->pCfg->pDrvBlinky);

    return finished;
}

static void RunState_Cyclic_Running(RunState* const pRunState)
{
    DrvBlinky_Cyclic(pRunState->pCfg->pDrvBlinky);

    /* Read the encoder driven counter value */
    pRunState->data.encoderAB = DrvTimer_GetCurrentValue(pRunState->pCfg->pEncoderAB);

    /* Read the latest converted ADC raw values for each axis*/
    uint32_t joystickX_Raw = HAL_ADC_GetValue(&hadc3);
    uint32_t joystickY_Raw = HAL_ADC_GetValue(&hadc4);

    /* Convert the adc values in ranges from 0 to 100 */
    uint32_t joystickX = (joystickX_Raw * VALUE_TO_PERCENT) / UINT12_MAX_VALUE;
    uint32_t joystickY = (joystickY_Raw * VALUE_TO_PERCENT) / UINT12_MAX_VALUE;

    /* Update the LED D4 PWM on EduShield by x-axis of joystick */
    /* Convert the range of x-axis to PWM length in digits */
    uint32_t pwmMaxValue = LL_TIM_GetAutoReload(htim4.Instance);
    uint32_t pwmNormalized = (joystickX * pwmMaxValue) / VALUE_TO_PERCENT;

    /* Write to Output compare value to define PWM for channel 3 */
    LL_TIM_OC_SetCompareCH3(htim4.Instance, pwmNormalized);

    /* Update the separate RGB LED board by y-axis of joystick */
    /* Convert the range of y-axis to PWM length in digits */
    pwmMaxValue = LL_TIM_GetAutoReload(htim3.Instance);
    pwmNormalized = (joystickY * pwmMaxValue) / VALUE_TO_PERCENT;

    /* Update all three RGB channels linearly to obtain always a white light*/
    LL_TIM_OC_SetCompareCH1(htim3.Instance, pwmNormalized);
    LL_TIM_OC_SetCompareCH3(htim3.Instance, pwmNormalized);
    LL_TIM_OC_SetCompareCH4(htim3.Instance, pwmNormalized);
}

static void RunState_Cyclic_Error(RunState const* pRunState)
{
    assert_param(0);
}

/*******************************************************************************
* Functions
*******************************************************************************/

void RunState_Construct(RunState* const pThis, RunStateConfig const* const pCfg)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == false);
    assert_param(pCfg != NULL);

    pThis->pCfg = pCfg;

    pThis->initialized = false;
    pThis->constructed = true;
}

void RunState_Init(RunState* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->initialized == false);
    assert_param(pThis->constructed == true);

    /* Initialize the modules */
    DrvCrc_Init(pThis->pCfg->pDrvCrc);

    DrvBlinky_Init(pThis->pCfg->pDrvBlinky);

    DrvTimer_Init(pThis->pCfg->pEncoderAB);

    pThis->data.state = RunState_SelfTest;
    pThis->data.encoderAB = 0u;

    ADC_Enable(&hadc3);
    ADC_Enable(&hadc4);

    HAL_ADC_Start(&hadc3);
    HAL_ADC_Start(&hadc4);

    pThis->initialized = true;
}

void RunState_Cyclic(RunState* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == true);
    assert_param(pThis->initialized == true);

    pThis->data.cycleCounter++;

    if (pThis->data.state == RunState_SelfTest)
    {
        bool error = false;

        if (RunState_Cyclic_SelfTest(pThis, &error))
        {
            if (error == true)
            {
                pThis->data.state = RunState_Error;
            }

            else
            {
                pThis->data.state = RunState_Running;
            }
        }
    }

    else if (pThis->data.state == RunState_Running)
    {
        RunState_Cyclic_Running(pThis);
    }

    else
    {
        RunState_Cyclic_Error(pThis);
    }
}


