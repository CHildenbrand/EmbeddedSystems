/**
 * @file      wait_state.c
 * @author    Christian Hildenbrand
 * @date      05.11.2023
 *
 * @brief [description]
 */

/*******************************************************************************
* Includes
*******************************************************************************/

#include "wait_state.h"

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

void WaitState_Construct(WaitState* const pThis, WaitStateCfg const* const pCfg)
{
    assert_param(pThis != NULL);
    assert_param(pThis->initialized == false);
    assert_param(pThis->constructed == false);

    pThis->pCfg = pCfg;

    pThis->constructed = true;
    pThis->initialized = false;
}

void WaitState_Init(WaitState* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == true);
    assert_param(pThis->initialized == false);

    DrvTimer_Init(pThis->pCfg->pDrvTimer);

    pThis->data.waitTimerExeeded = false;

    pThis->initialized = true;
}

void WaitState_Cyclic(WaitState* const pThis)
{
    if (DrvTimer_IsTimerReloaded(pThis->pCfg->pDrvTimer))
    {
        pThis->data.waitTimerExeeded = true;
    }

    else
    {
        while (DrvTimer_IsTimerReloaded(pThis->pCfg->pDrvTimer) == false)
        {
            /* just wait */
        }

        DrvTimer_ClearReloaded(pThis->pCfg->pDrvTimer);
    }
}

bool WaitState_IsError(WaitState* const pThis)
{
    return pThis->data.waitTimerExeeded;
}

