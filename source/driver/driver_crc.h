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

typedef enum
{
    DrvCrcState_Initial,

    DrvCrcState_Calculating,

    DrvCrcState_Finished,
} DrvCrcState;

typedef struct
{
    bool isHardwareCrc;

    DMA_HandleTypeDef *pHdma;

    CRC_HandleTypeDef *pHcrc;

    const uint32_t crcRangeStartAddress;

    const uint32_t crcRangeEndAddress;

    const uint32_t dstAddress;

    const uint32_t *pCrcAddress;
} DrvCrcCfg;

typedef struct
{
    DrvCrcState state;

    bool isValid;

    uint32_t crc_value;
} DrvCrcData;


typedef struct
{
    bool initialized;

    bool constructed;

    DrvCrcCfg const* pCfg;

    DrvCrcData data;
} DrvCrc;

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Exported Functions
*******************************************************************************/

void DrvCrc_Construct(DrvCrc *const pThis, DrvCrcCfg const* const pCfg);

void DrvCrc_Init(DrvCrc *const pThis);

void DrvCrc_Cyclic(DrvCrc *const pThis);

DrvCrcState DrvCrc_GetState (DrvCrc const* const pThis);

bool DrvCrc_IsValid(DrvCrc const* const pThis);


#endif /* DRIVER_CRC_H_ */
