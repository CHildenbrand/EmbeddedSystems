/**
 * @file      ctor_all.c
 * @author    AsusV
 * @date      06.05.2023
 *
 * @brief [description]
 */

/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "main_state.h"
#include "main.h"

#include "dma.h"
#include "crc.h"

/*******************************************************************************
* Defines
*******************************************************************************/

//#define FLASH_CRC_START_ADDRESS 		(uint32_t)(0x8000000UL)
//#define FLASH_CRC_END_ADDRESS    		(uint32_t)(0x8001000UL)

#define NUMBER_OF_LEDS 					1u
#define LD2_USER_LED_IDX 				0u
#define BLINKY_CYCLE_MAIN_CYCLE_COUNT 	100000u

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Global Variables
*******************************************************************************/
extern const uint32_t __END_CRC_FLASH[];
extern const uint32_t __START_CRC_FLASH[];

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Static Variables
*******************************************************************************/

/*******************************************************************************
* Functions
*******************************************************************************/

void CtorAll_Construct(MainState *const pThis)
{

    static DrvBlinky m_drvBlinky;

    static DrvCrc m_drvCrc;

    static DrvCrcCfg m_drvCrcCfg =
    {
        .pHdma = &hdma_memtomem_dma1_channel1,
        .pHcrc = &hcrc,
        .dstAddress = (uint32_t)&CRC->DR,
        .isHardwareCrc = true,
        .crcRangeStartAddress = (const uint32_t)__START_CRC_FLASH,
        .crcRangeEndAddress = (const uint32_t)__END_CRC_FLASH,
        .pCrcAddress = (const uint32_t *)__END_CRC_FLASH
    };

    DrvCrc_Construct(&m_drvCrc, &m_drvCrcCfg);

    static DrvGpio m_drvGpio =
    {
        .ledPort = LD2_USER_GPIO_Port,
        .ledPin = LD2_USER_Pin,
        .initValue = GPIO_PIN_RESET,
        .currentValue = GPIO_PIN_RESET
    };

    static DrvBlinkyCfg m_drvBlinkyCfg =
    {
        .numberOfLeds = NUMBER_OF_LEDS,
        .blinkyCycleTotal = BLINKY_CYCLE_MAIN_CYCLE_COUNT,
        .pDrvGpio = &m_drvGpio
    };

    DrvBlinky_Construct(&m_drvBlinky, &m_drvBlinkyCfg);

    static MainStateConfig m_mainStateCfg =
    {
        .pDrvBlinky =  &m_drvBlinky,
        .pDrvCrc =  &m_drvCrc,
    };

    MainState_Construct(pThis, &m_mainStateCfg);
}
