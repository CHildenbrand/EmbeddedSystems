/**
 * @file      driver_crc.c
 * @author    Hildenbrand, Christian
 * @date      06.05.2023
 *
 * @brief [description]
 */

/*******************************************************************************
* Includes
*******************************************************************************/
#include "driver_crc.h"
#include "stm32g4xx_ll_crc.h"

/*******************************************************************************
* Defines
*******************************************************************************/

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Static Variables
*******************************************************************************/

static bool m_crcAvailable = false;

/*******************************************************************************
* Static Functions
*******************************************************************************/

static void DrvCrc_HandleDmaTxComplete(DMA_HandleTypeDef* pHdma)
{
    m_crcAvailable = true;
}

/*******************************************************************************
* Public Functions
*******************************************************************************/

void DrvCrc_Construct(DrvCrc* const pThis, DrvCrcCfg const* const pCfg)
{
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == false);
    assert_param(pCfg != NULL);

    pThis->pCfg = pCfg;

    pThis->initialized = false;
    pThis->constructed = true;
}

void DrvCrc_Init(DrvCrc* const pThis)
{
    /* Initialize Object only if pointer not null and constructed */
    assert_param(pThis != NULL);
    assert_param(pThis->constructed == true);

    /* Initialize runtime data */
    pThis->data.state = DrvCrcState_Initial;
    pThis->data.isValid = false;

    if (pThis->pCfg->isHardwareCrc)
    {
        (void)HAL_DMA_RegisterCallback(pThis->pCfg->pHdma, HAL_DMA_XFER_CPLT_CB_ID, &DrvCrc_HandleDmaTxComplete);

        uint32_t dataLength = (pThis->pCfg->crcRangeEndAddress - pThis->pCfg->crcRangeStartAddress) / sizeof(uint32_t);

        /* Configure and Start DMA Peripheral */
        HAL_DMA_Start_IT(pThis->pCfg->pHdma, pThis->pCfg->crcRangeStartAddress, pThis->pCfg->dstAddress, dataLength);

        pThis->data.state = DrvCrcState_Calculating;
    }

    pThis->initialized = true;
}

void DrvCrc_Cyclic(DrvCrc* const pThis)
{
    assert_param(pThis != NULL);
    assert_param(pThis->initialized == true);

    if (pThis->data.state == DrvCrcState_Calculating)
    {
        if (m_crcAvailable == true)
        {
            /* crc-32 with XorOut=0xFFFFFFFF */
            pThis->data.crc_value = ~LL_CRC_ReadData32(pThis->pCfg->pHcrc->Instance);

            uint32_t crc_value_flash = pThis->pCfg->pCrcAddress[0u];

            if (crc_value_flash == pThis->data.crc_value)
            {
                pThis->data.isValid = true;
            }

            pThis->data.state = DrvCrcState_Finished;

            m_crcAvailable = false;
        }
    }
}

DrvCrcState DrvCrc_GetState(DrvCrc const* const pThis)
{
    return pThis->data.state;
}

bool DrvCrc_IsValid(DrvCrc const* const pThis)
{
    return pThis->data.isValid;
}
