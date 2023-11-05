/**
 * @file      driver_crc.h
 * @author    Hildenbrand, Christian
 * @date      06.05.2023
 *
 * @brief [description]
 */

#ifndef DRIVER_CRC_H_
#define DRIVER_CRC_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>

#include "stm32g4xx_hal.h"

/*******************************************************************************
* Exported Defines
*******************************************************************************/

/*******************************************************************************
* Exported Types and Typedefs
*******************************************************************************/

/*! Enumeration of current Background Crc calculation */
typedef enum
{
    DrvCrcState_Initial,

    DrvCrcState_Calculating,

    DrvCrcState_Finished,
} DrvCrcState;

/*! Configuration structure storing all infos requred for background calculation */
typedef struct
{
    /*! Indication if Crc is calculated by hardware accelerator */
    bool isHardwareCrc;

    /*! Pointer to DMA Handler from STM driver */
    DMA_HandleTypeDef* pHdma;

    /*! Pointer to CRC Handler from STM driver */
    CRC_HandleTypeDef* pHcrc;

    /*! Value representing the start address (including) for crc caclulation */
    const uint32_t crcRangeStartAddress;

    /*! Value representing the end address (excluding) for crc calculation */
    const uint32_t crcRangeEndAddress;

    /*! Destination address for copy operations of DMA */
    const uint32_t dstAddress;

    /*! Location of PostBuild caclulated crc of flash footprint */
    const uint32_t* pCrcAddress;
} DrvCrcCfg;

/*! Runtime Data of \ref DrvCrc object */
typedef struct
{
    /*! Current state of CRC Background calulation */
    DrvCrcState state;

    /*! Indication if runtime caluclated crc matches postBuild caluclated value */
    bool isValid;

    /*! Valid crc raw value */
    uint32_t crc_value;
} DrvCrcData;

/*! Typedefinition of \ref DrvCrc object */
typedef struct
{
    /*! Initialization flag */
    bool initialized;

    /*! Construction flag */
    bool constructed;

    /*! Pointer to \ref DrvCrcCfg */
    DrvCrcCfg const* pCfg;

    /*! Runtime data of object */
    DrvCrcData data;
} DrvCrc;

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Exported Functions
*******************************************************************************/

/*!
 * \brief Constructs the \ref DrvCrc object
 *
 * \param pThis Pointer to \ref DrvCrc object
 * \param pCfg Pointer to \ref DrvCrcCfg
 */
void DrvCrc_Construct(DrvCrc* const pThis, DrvCrcCfg const* const pCfg);


/*!
 * \brief Initializes the \ref DrvCrc object
 *
 * \param pThis Pointer to \ref DrvCrc object
 */
void DrvCrc_Init(DrvCrc* const pThis);

/*!
 * \brief Cyclic processing of the \ref DrvCrc object
 *
 * \param pThis Pointer to \ref DrvCrc object
 */
void DrvCrc_Cyclic(DrvCrc* const pThis);

/*!
 * \brief Returns the current calculation status of the \ref DrvCrc object
 *
 * \param pThis Pointer to \ref DrvCrc object
 * \return Current Calucation status
 */
DrvCrcState DrvCrc_GetState(DrvCrc const* const pThis);

/*!
 * \brief Returns flag of crc validation
 *
 * \param pThis Pointer to \ref DrvCrc object
 * \return True if Crc is valid, false if not proven valid
 */
bool DrvCrc_IsValid(DrvCrc const* const pThis);

#endif /* DRIVER_CRC_H_ */
