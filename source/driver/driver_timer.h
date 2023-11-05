/**
 * @file      driver_timer.c
 * @author    Christian Hildenbrand
 * @date      05.11.2023
 *
 * @brief [description]
 */

#ifndef DRIVER_TIMER_H_
#define DRIVER_TIMER_H_

/*******************************************************************************
* Includes
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_tim.h"

/*******************************************************************************
* Defines
*******************************************************************************/

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

typedef enum
{
    DrvTimer_MsTimer,

    DrvTimer_UsTimer,

    DrvTimer_TickTimer

} DrvTimerType;

/*! Configuration of Driver Timer  */
typedef struct
{
    /*! Pointer to \ref TIM_HandleTypeDef object */
    TIM_HandleTypeDef* const pTim;

    DrvTimerType type;

    uint32_t ticksPerSecond;

    uint32_t waitTimeInit;
} DrvTimerCfg;

/*! Runtime Data of Driver Timer object */
typedef struct
{
    /*! Last stored time stamp */
    uint32_t timeStamp;

    /*! Time to Wait in Timer Resolution */
    uint32_t waitTime;

} DrvTimerData;

/*! Structure definition of DrvTimer object */
typedef struct
{
    /*! Constuction Flag */
    bool constructed;

    /*! Pointer to \ref WaitStateCfg object */
    DrvTimerCfg const* pCfg;

    /*! Initalization Flag */
    bool initialized;

    /*! Runtime Data */
    DrvTimerData data;

} DrvTimer;

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

void DrvTimer_Construct(DrvTimer* const pThis, DrvTimerCfg const* const pCfg);

void DrvTimer_Init(DrvTimer* const pThis);

uint32_t DrvTimer_GetCurrentValue(DrvTimer* const pThis);

void DrvTimer_SetCurrentvalue(DrvTimer* const pThis);

bool DrvTimer_IsTimerReloaded(DrvTimer const* const pThis);

void DrvTimer_ClearReloaded(DrvTimer* const pThis);

bool DrvTimer_IsTimeElapsed(DrvTimer const* const pThis);

#endif /* DRIVER_TIMER_H_ */
