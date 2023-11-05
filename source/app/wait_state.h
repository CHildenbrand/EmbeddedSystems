/**
 * @file      wait_state.h
 * @author    Christian Hildenbrand
 * @date      05.11.2023
 *
 * @brief [description]
 */

#ifndef WAIT_STATE_H_
#define WAIT_STATE_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>
#include <stdint.h>

#include "driver_timer.h"

/*******************************************************************************
* Defines
*******************************************************************************/

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*! Configuration of Wait SAte  */
typedef struct
{
    /*! Pointer to \ref DrvTimer object */
    DrvTimer* const pDrvTimer;

} WaitStateCfg;

/*! Runtime Data of Wait State object */
typedef struct
{
    /*! Flag indicating that cycle time was exceeded */
    bool waitTimerExeeded;

} WaitStateData;

/*! Structure definition of DrvTimer object */
typedef struct
{
    /*! Constuction Flag */
    bool constructed;

    /*! Pointer to \ref WaitStateCfg object */
    WaitStateCfg const* pCfg;

    /*! Initalization Flag */
    bool initialized;

    /*! Runtime Data */
    WaitStateData data;

} WaitState;

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

void WaitState_Construct(WaitState* const pThis, WaitStateCfg const* const pCfg);

void WaitState_Init(WaitState* const pThis);

void WaitState_Cyclic(WaitState* const pThis);

bool WaitState_IsError(WaitState* const pThis);

#endif /* WAIT_STATE_H_ */
