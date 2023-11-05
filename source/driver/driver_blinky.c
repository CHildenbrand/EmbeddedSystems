/**
 * @file      driver_blinky.c
 * @author    Hildenbrand, Christian
 * @date      06.05.2023
 *
 * @brief This module abstracts the blinky functionality of a LED
 *
 * \details This module groups GPIOs dedicated to simple binary LEDs. The LED
 * shows different illumination pattern such as constantly on / off or blinking
 * with a period in multiply calls of DrvBlinky_MainCycle calls.
 */

/*******************************************************************************
* Includes
*******************************************************************************/

#include "driver_blinky.h"

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

static void DrvBlinky_InitPin(DrvGpio* const pDrvGpio)
{
    HAL_GPIO_WritePin(pDrvGpio->ledPort, pDrvGpio->ledPin, pDrvGpio->initValue);

    pDrvGpio->currentValue = pDrvGpio->initValue;
}


static void DrvBlinky_SetPin(DrvGpio* const pDrvGpio)
{
    HAL_GPIO_WritePin(pDrvGpio->ledPort, pDrvGpio->ledPin, GPIO_PIN_SET);

    pDrvGpio->currentValue = GPIO_PIN_SET;
}

static void DrvBlinky_ResetPin(DrvGpio* const pDrvGpio)
{
    HAL_GPIO_WritePin(pDrvGpio->ledPort, pDrvGpio->ledPin, GPIO_PIN_RESET);

    pDrvGpio->currentValue = GPIO_PIN_RESET;
}

static void DrvBlinky_TogglePin(DrvGpio* const pDrvGpio)
{
    if (pDrvGpio->currentValue != GPIO_PIN_RESET)
    {
        DrvBlinky_ResetPin(pDrvGpio);
    }

    else
    {
        DrvBlinky_SetPin(pDrvGpio);
    }
}

/*******************************************************************************
* Functions
*******************************************************************************/

void DrvBlinky_Construct(DrvBlinky* const pThis, DrvBlinkyCfg const* const pCfg)
{
    assert_param(pThis->constructed == false);

    pThis->pCfg = pCfg;

    pThis->constructed = true;
}


void DrvBlinky_Init(DrvBlinky* const pThis)
{
    /* Initialize Object only if pointer not null and constructed */
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == true);

    DrvBlinky_InitPin(pThis->pCfg->pDrvGpio);

    pThis->initialized = true;
}


void DrvBlinky_Cyclic(DrvBlinky* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->initialized == true);

    if (pThis->data.state == DrvBlinkyState_On)
    {
        DrvBlinky_SetPin(pThis->pCfg->pDrvGpio);
    }

    else if (pThis->data.state  == DrvBlinkyState_Off)
    {
        DrvBlinky_ResetPin(pThis->pCfg->pDrvGpio);
    }

    else if (pThis->data.state  == DrvBlinkyState_Blinky)
    {
        pThis->data.blinkyCycleCnt++;

        /* Number of wait cycles exceed period */
        if (pThis->data.blinkyCycleCnt >= pThis->pCfg->blinkyCycleTotal)
        {
            DrvBlinky_TogglePin(pThis->pCfg->pDrvGpio);

            pThis->data.blinkyCycleCnt = 0u;
        }
    }
}

void DrvBlinky_SetState(DrvBlinky* const pThis, DrvBlinkyState state)
{
    assert_param(pThis != NULL);
    assert_param(pThis->initialized == true);

    pThis->data.state = state;
}
