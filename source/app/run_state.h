/**
 * @file      run_state.h
 * @author    Christian Hildenbrand
 * @date      01.05.2023
 *
 * @brief Header File for Main State Module
 */

#ifndef RUN_STATE_H_
#define RUN_STATE_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>

#include "driver_blinky.h"
#include "driver_crc.h"
#include "driver_timer.h"

/*******************************************************************************
* Exported Defines
*******************************************************************************/

/*******************************************************************************
* Exported Types and Typedefs
*******************************************************************************/

/*! Enumeration of Main State Values */
typedef enum
{
    RunState_Initial,

    RunState_SelfTest,

    RunState_Running,

    RunState_Error,
} RunState_State;

/*! Configuration of Main State */
typedef struct
{
    /*! Pointer to \ref DrvCrc object */
    DrvCrc* const pDrvCrc;

} RunStateConfig;

/*! Runtime Data of Main State object */
typedef struct
{
    /*! Current State of Main State machine */
    RunState_State state;

    /*! Number of RunState calls */
    uint32_t cycleCounter;

} RunState_Data;

/*! Structure definition of RunState object */
typedef struct
{
    /*! Constuction Flag */
    bool constructed;

    /*! Pointer to \ref RunStateConfig object */
    RunStateConfig const* pCfg;

    /*! Initialization Flag */
    bool initialized;

    /*! Runtime Data */
    RunState_Data data;

} RunState;

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Exported Functions
*******************************************************************************/

/*!
 * \brief Function constructs the \ref RunState object
 *
 * \param pThis Pointer to \ref RunState
 * \param pCfg Pointer to \ref RunStateConfig
 */
void RunState_Construct(RunState* const pThis, RunStateConfig const* const pCfg);

/*!
 * \brief Function initalizes the \ref RunState object
 *
 * \param pThis Pointer to \ref RunState
 */
void RunState_Init(RunState* const pThis);

/*!
 * \brief Cyclic processing of the \ref RunState object
 *
 * \param pThis Pointer to \ref RunState
 */
void RunState_Cyclic(RunState* const pThis);

#endif /* RUN_STATE_H_ */
