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

static bool MainState_Cyclic_SelfTest(MainState const* pMainState, bool* pError)
{
    bool finished = false;

    DrvCrc_Cyclic(pMainState->pCfg->pDrvCrc);

    if (DrvCrc_GetState(pMainState->pCfg->pDrvCrc) == DrvCrcState_Finished)
    {

        if (DrvCrc_IsValid(pMainState->pCfg->pDrvCrc) != false)
        {
            DrvBlinky_SetState(pMainState->pCfg->pDrvBlinky, DrvBlinkyState_Blinky);
        }

        else
        {
            DrvBlinky_SetState(pMainState->pCfg->pDrvBlinky, DrvBlinkyState_On);
        }

        finished = true;
    }

    DrvBlinky_Cyclic(pMainState->pCfg->pDrvBlinky);

    return finished;
}

static void MainState_Cyclic_Running(MainState const* pMainState)
{
    DrvBlinky_Cyclic(pMainState->pCfg->pDrvBlinky);
}

static void MainState_Cyclic_Error(MainState const* pMainState)
{
    assert_param(0);
}

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
    volatile uint32_t wait = 100000u;

    while (wait--) {}

    assert_param(pThis != NULL);
    assert_param(pThis->initialized == false);
    assert_param(pThis->constructed == true);

    /* Construct all modules */
    CtorAll_Construct(pThis);

    /* Initialize the modules */
    DrvCrc_Init(pThis->pCfg->pDrvCrc);

    DrvBlinky_Init(pThis->pCfg->pDrvBlinky);

    pThis->data.state = MainState_SelfTest;

    pThis->initialized = true;
}

void MainState_Cyclic(MainState* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == true);
    assert_param(pThis->initialized == true);

    pThis->data.cycleCounter++;

    if (pThis->data.state == MainState_SelfTest)
    {
        bool error = false;

        if (MainState_Cyclic_SelfTest(pThis, &error))
        {
            if (error == true)
            {
                pThis->data.state = MainState_Error;
            }

            else
            {
                pThis->data.state = MainState_Running;
            }
        }
    }

    else if (pThis->data.state == MainState_Running)
    {
        MainState_Cyclic_Running(pThis);
    }

    else if (pThis->data.state == MainState_Error ||
             pThis->data.state == MainState_Initial)
    {
        MainState_Cyclic_Error(pThis);
    }
}


