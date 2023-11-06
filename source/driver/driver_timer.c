/**
 * @file      driver_timer.c
 * @author    Christian Hildenbrand
 * @date      05.11.2023
 *
 * @brief [description]
 */

/*******************************************************************************
* Includes
*******************************************************************************/

#include "driver_timer.h"

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

void DrvTimer_Construct(DrvTimer* const pThis, DrvTimerCfg const* const pCfg)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == false);
    assert_param(pThis->initialized == false);

    pThis->pCfg = pCfg;

    pThis->constructed = true;

}

void DrvTimer_Init(DrvTimer* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == true);
    assert_param(pThis->initialized == false);

    DrvTimer_ClearReloaded(pThis);
    LL_TIM_EnableCounter(pThis->pCfg->pTim->Instance);

    pThis->data.waitTime = pThis->pCfg->waitTimeInit;

    pThis->initialized = true;
}

uint32_t DrvTimer_GetReloadValue(DrvTimer const* const pThis)
{
    return LL_TIM_GetAutoReload(pThis->pCfg->pTim->Instance);
}

uint32_t DrvTimer_GetCurrentValue(DrvTimer* const pThis)
{
    return LL_TIM_GetCounter(pThis->pCfg->pTim->Instance);
}

void DrvTimer_SetCurrentvalue(DrvTimer* const pThis)
{
    pThis->data.timeStamp = LL_TIM_GetCounter(pThis->pCfg->pTim->Instance);
}

bool DrvTimer_IsTimerReloaded(DrvTimer const* const pThis)
{
    return LL_TIM_IsActiveFlag_UPDATE(pThis->pCfg->pTim->Instance);
}

void DrvTimer_ClearReloaded(DrvTimer* const pThis)
{
    LL_TIM_ClearFlag_UPDATE(pThis->pCfg->pTim->Instance);
}

bool DrvTimer_IsTimeElapsed(DrvTimer const* const pThis)
{
    bool isElapsed = false;

    uint32_t currentTime = LL_TIM_GetCounter(pThis->pCfg->pTim->Instance);
    uint32_t reloadValue = LL_TIM_GetAutoReload(pThis->pCfg->pTim->Instance);

    /* positive logic */
    if (LL_TIM_GetCounterMode(pThis->pCfg->pTim->Instance) == LL_TIM_COUNTERMODE_UP)
    {
        if (currentTime > pThis->data.timeStamp)
        {
            if (pThis->data.timeStamp - currentTime > pThis->data.waitTime)
            {
                isElapsed = true;
            }
        }

        else /* timer overflow */
        {
            if ((reloadValue - pThis->data.timeStamp) + currentTime + 1UL > pThis->data.waitTime)
            {
                isElapsed = true;
            }
        }
    }

    /* TODO: Implement inverse logic for downcounting timers */
    return isElapsed;
}

