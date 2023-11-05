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

/*! Enlightings states of the dedicated LED */
typedef enum
{
    DrvBlinkyState_On,

    DrvBlinkyState_Off,

    DrvBlinkyState_Blinky
} DrvBlinkyState;

/*! Typedef of Driver Gpio object */
typedef struct
{
    /*! Pointer to GPIO port */
    GPIO_TypeDef* ledPort;

    /*! Number of GPIO Pin */
    uint16_t ledPin;

    /*! Initalization value of Pin */
    GPIO_PinState initValue;

    /*! Current value of pin */
    GPIO_PinState currentValue;
} DrvGpio;

/*! Configuration structure definition of Driver Blinky */
typedef struct
{
    /*! Number of LEDs dedicated for this Blinky stucture */
    uint32_t numberOfLeds;

    /*! Blinky Main Cycle count to toggle LED status */
    uint32_t blinkyCycleTotal;

    /*! Pointer to \ref DrvGpio object */
    DrvGpio* pDrvGpio;
} DrvBlinkyCfg;

/*! Runtime data of \ref DrvBlinky object */
typedef struct
{
    /*! Blink pattern for Blinky group */
    DrvBlinkyState state;

    /*! Current decrementing cycle count to wait for toggling */
    uint32_t blinkyCycleCnt;
} DrvBlinkyData;

/*! Structure definition of DrvBlinky object */
typedef struct
{
    /*! Initialization flag */
    bool initialized;

    /*! Construction flag */
    bool constructed;

    /*! Pointer to \ref DrvBlinkyCfg */
    DrvBlinkyCfg const* pCfg;

    /*! Runtime Data of DrvBlinky object */
    DrvBlinkyData data;
} DrvBlinky;

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Exported Functions
*******************************************************************************/

/*!
 * \brief Constructs the \ref DrvBlinky object
 *
 * \param pThis Pointer to \ref DrvBlinky object
 * \param pCfg Pointer to \ref DrvBlinkyCfg
 */
void DrvBlinky_Construct(DrvBlinky* const pThis, DrvBlinkyCfg const* const pCfg);


/*!
 * \brief Initalizes the \ref DrvBlinky object
 *
 * \param pThis Pointer to \ref DrvBlinky object
 */
void DrvBlinky_Init(DrvBlinky* const pThis);

/*!
 * \brief Cyclic processing of the \ref DrvBlinky object
 *
 * \param pThis Pointer to \ref DrvBlinky object
 */
void DrvBlinky_Cyclic(DrvBlinky* const pThis);

/*!
 * \brief Sets the blinky pattern for \ref DrvBlinky object
 *
 * \param pThis Pointer to \ref DrvBlinky object
 * \param state Input Blinky Pattern
 */
void DrvBlinky_SetState(DrvBlinky* const pThis, DrvBlinkyState state);

#endif /* DRIVER_BLINKY_H_ */
