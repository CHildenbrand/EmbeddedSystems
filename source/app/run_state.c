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

    /* Read 16 bit encoder detent raw value and convert to int16 */
    pRunState->data.encoderAB = ((int16_t)htim20.Instance->CNT);
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

    pThis->data.state = RunState_SelfTest;
    pThis->data.encoderAB = 0;

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


