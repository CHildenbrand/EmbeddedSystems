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

#include "main_state.h"
#include "driver_blinky.h"
#include "driver_crc.h"
#include "stm32g4xx_hal_gpio.h"
#include "ctor_all.h"
#include "main.h"

/*******************************************************************************
* Defines
*******************************************************************************/

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

/*******************************************************************************
* Functions
*******************************************************************************/

void MainState_Construct(MainState* const pThis, MainStateConfig const* const pCfg)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == false);
    assert_param(pCfg != NULL);

    pThis->pCfg = pCfg;

    pThis->initialized = false;
    pThis->constructed = true;
}

void MainState_Init(MainState* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->initialized == false);
    assert_param(pThis->constructed == true);

    /* Construct all modules */
    CtorAll_Construct(pThis);

    RunState_Init(pThis->pCfg->pRunState);
    WaitState_Init(pThis->pCfg->pWaitState);

    pThis->data.state = MainState_Run;

    pThis->initialized = true;
}

void MainState_Cyclic(MainState* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == true);
    assert_param(pThis->initialized == true);

    pThis->data.cycleCounter++;

    if (pThis->data.state == MainState_Run)
    {
        RunState_Cyclic(pThis->pCfg->pRunState);

        pThis->data.state = MainState_Wait;
    }

    else if (pThis->data.state == MainState_Wait)
    {
        WaitState_Cyclic(pThis->pCfg->pWaitState);

        if (WaitState_IsError(pThis->pCfg->pWaitState))
        {
            pThis->data.state = MainState_Error;
        }

        else
        {
            pThis->data.state = MainState_Run;
        }
    }

    else
    {
        Error_Handler();
    }
}


