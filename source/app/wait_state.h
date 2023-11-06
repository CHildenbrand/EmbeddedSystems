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

/*! Configuration Structure of Wait State  */
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

    /*! CPU Load in Percent */
    float cpuLoadPercent;

} WaitStateData;

/*! Structure definition of WaitState object */
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

/*!
 * \brief Constructs the \ref WaitState object
 *
 * \param pThis Pointer to \ref WaitState object
 * \param pCfg Pointer to \ref WaitStateCfg
 */
void WaitState_Construct(WaitState* const pThis, WaitStateCfg const* const pCfg);

/*!
 * \brief Initializes the \ref WaitState object
 *
 * \param pThis Pointer to \ref WaitState object
 */
void WaitState_Init(WaitState* const pThis);

/*!
 * \brief Cyclic processing of the \ref WaitState object
 *
 * \param pThis Pointer to \ref WaitState object
 */
void WaitState_Cyclic(WaitState* const pThis);

/*!
 * \brief Gets the internal error state of the \ref WaitState object
 *
 * \param pThis Pointer to \ref WaitState object
 * \return True if WaitState is in internal error; False else
 */
bool WaitState_IsError(WaitState* const pThis);

#endif /* WAIT_STATE_H_ */
