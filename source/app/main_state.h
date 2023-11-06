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

#include "run_state.h"
#include "wait_state.h"

/*******************************************************************************
* Exported Defines
*******************************************************************************/

/*******************************************************************************
* Exported Types and Typedefs
*******************************************************************************/

/*! Enumeration of Main State Values */
typedef enum
{
    MainState_Initial,

    MainState_Run,

    MainState_Wait,

    MainState_Error,
} MainState_State;

/*! Configuration of Main State */
typedef struct
{
    /*! Pointer to \ref RunState object */
    RunState* const pRunState;

    /*! Pointer to \ref WaitState object */
    WaitState* const pWaitState;

} MainStateConfig;

/*! Runtime Data of Main State object */
typedef struct
{
    /*! Current State of Main State machine */
    MainState_State state;

    /*! Number of MainState calls */
    uint32_t cycleCounter;
} MainState_Data;

/*! Structure definition of MainState object */
typedef struct
{
    /*! Constuction Flag */
    bool constructed;

    /*! Pointer to \ref MainStateConfig object */
    MainStateConfig const* pCfg;

    /*! Initalization Flag */
    bool initialized;

    /*! Runtime Data */
    MainState_Data data;

} MainState;

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Exported Functions
*******************************************************************************/

/*!
 * \brief Function constructs the \ref MainState object
 *
 * \param pThis Pointer to \ref MainState
 * \param pCfg Pointer to \ref MainStateConfig
 */
void MainState_Construct(MainState* const pThis, MainStateConfig const* const pCfg);

/*!
 * \brief Function initializes the \ref MainState object
 *
 * \param pThis Pointer to \ref MainState
 */
void MainState_Init(MainState* const pThis);

/*!
 * \brief Cyclic processing of the \ref MainState object
 *
 * \param pThis Pointer to \ref MainState
 */
void MainState_Cyclic(MainState* const pThis);

#endif /* MAIN_STATE_H_ */
