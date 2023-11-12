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

/*! Enumeration of DrvTimer Types */
typedef enum
{
    DrvTimer_MsTimer,

    DrvTimer_UsTimer,

    DrvTimer_TickTimer,

    DrvTimer_EncoderAB,

} DrvTimerType;

/*! Configuration of Driver Timer  */
typedef struct
{
    /*! Pointer to TIM_HandleTypeDef object */
    TIM_HandleTypeDef* const pTim;

    /*! Driver Timer Type */
    DrvTimerType type;

    /*! Value representing number of ticks for one second */
    uint32_t ticksPerSecond;

    /*! Time span to wait */
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

/*!
 * \brief Constructs the \ref DrvTimer object
 *
 * \param pThis Pointer to \ref DrvTimer object
 * \param pCfg Pointer to \ref DrvTimerCfg Configuration
 */
void DrvTimer_Construct(DrvTimer* const pThis, DrvTimerCfg const* const pCfg);

/*!
 * \brief Initializes the \ref DrvTimer object
 *
 * \param pThis Pointer to \ref DrvTimer object
 */
void DrvTimer_Init(DrvTimer* const pThis);


/*!
 * \brief Returns the time base reload value of peripheral dedicated to \ref DrvTimer
 *
 * \param pThis Pointer to \ref DrvTimer object
 * \return Reload Value of Timer peripheral
 */
uint32_t DrvTimer_GetReloadValue(DrvTimer const* const pThis);

/*!
 * \brief Get the current raw value of peripheral timer dedicated to \ref DrvTimer
 *
 * \param pThis Pointer to \ref DrvTimer object
 * \return Raw Value of corresponding timer counter
 */
uint32_t DrvTimer_GetCurrentValue(DrvTimer* const pThis);

/*!
 * \brief Stores the current timer value into the \ref DrvTimer object
 *
 * \param pThis Pointer to \ref DrvTimer object
 */
void DrvTimer_SetCurrentvalue(DrvTimer* const pThis);

/*!
 * \brief Returns reload flag of the \ref DrvTimer object
 *
 * \param pThis Pointer to \ref DrvTimer object
 * \return True if corresponding timer counter reloaded. False else
 */
bool DrvTimer_IsTimerReloaded(DrvTimer const* const pThis);

/*!
 * \brief Clears the reload flag for the \ref DrvTimer object
 *
 * \param pThis Pointer to \ref DrvTimer object
 */
void DrvTimer_ClearReloaded(DrvTimer* const pThis);

/*!
 * \brief Evaluates if time span currently exceeded of the \ref DrvTimer object
 *
 * \param pThis Pointer to \ref DrvTimer object
 * \return True if timer elapsed. False else.
 */
bool DrvTimer_IsTimeElapsed(DrvTimer const* const pThis);

#endif /* DRIVER_TIMER_H_ */
