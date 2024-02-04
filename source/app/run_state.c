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
            /* Nothing to do */
        }
        else
        {
            /* Nothing to do */
        }

        finished = true;
    }

    return finished;
}

static void RunState_Cyclic_Running(RunState* const pRunState)
{

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

    pThis->data.state = RunState_SelfTest;

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


