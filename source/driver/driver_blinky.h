/**
 * @file      driver_blinky.h
 * @author    Hildenbrand, Christian
 * @date      06.05.2023
 *
 * @brief [description]
 */

#ifndef DRIVER_BLINKY_H_
#define DRIVER_BLINKY_H_

/*******************************************************************************
* Includes
*******************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include "stm32g4xx_hal.h"

/*******************************************************************************
* Exported Defines
*******************************************************************************/

/*******************************************************************************
* Exported Types and Typedefs
*******************************************************************************/

typedef enum
{
    DrvBlinkyState_On,

    DrvBlinkyState_Off,

    DrvBlinkyState_Blinky
} DrvBlinkyState;


typedef struct
{
    GPIO_TypeDef* ledPort;

    uint16_t ledPin;

    GPIO_PinState initValue;

    GPIO_PinState currentValue;
} DrvGpio;

typedef struct
{
    uint32_t numberOfLeds;

    uint32_t blinkyCycleTotal;

    DrvGpio* pDrvGpio;
} DrvBlinkyCfg;

typedef struct
{
    DrvBlinkyState state;

    uint32_t blinkyCycleCnt;
} DrvBlinkyData;


typedef struct
{
    bool initialized;

    bool constructed;

    DrvBlinkyCfg const* pCfg;

    DrvBlinkyData data;
} DrvBlinky;

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Exported Functions
*******************************************************************************/

void DrvBlinky_Construct(DrvBlinky* const pThis, DrvBlinkyCfg const* const pCfg);

void DrvBlinky_Init(DrvBlinky* const pThis);

void DrvBlinky_Cyclic(DrvBlinky* const pThis);

void DrvBlinky_SetState(DrvBlinky* const pThis, DrvBlinkyState state);

#endif /* DRIVER_BLINKY_H_ */
