/**
 * @file      main_state.h
 * @author    Christian Hildenbrand
 * @date      01.05.2023
 *
 * @brief Header File for Main State Module
 */

#ifndef MAIN_STATE_H_
#define MAIN_STATE_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>

#include "driver_blinky.h"
#include "driver_crc.h"

/*******************************************************************************
* Exported Defines
*******************************************************************************/

/*******************************************************************************
* Exported Types and Typedefs
*******************************************************************************/

typedef enum
{
    MainState_Initial,

    MainState_Idle,

    MainState_SelfTest,

    MainState_Running,

    MainState_Error,
} MainState_State;

typedef struct
{
    DrvBlinky* const pDrvBlinky;

    DrvCrc* const pDrvCrc;
} MainStateConfig;

typedef struct
{
    MainState_State state;

    uint32_t cycleCounter;
} MainState_Data;

typedef struct
{
    bool constructed;

    MainStateConfig const* pCfg;

    bool initialized;

    MainState_Data data;

} MainState;

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Exported Functions
*******************************************************************************/

void MainState_Construct(MainState* const pThis, MainStateConfig const* const pCfg);

void MainState_Init(MainState* const pThis);

void MainState_Cyclic(MainState* const pThis);

#endif /* MAIN_STATE_H_ */
