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
#include "tim.h"

#include "run_state.h"
#include "wait_state.h"

/*******************************************************************************
* Defines
*******************************************************************************/

/*! Number of LEDs configured as DrvGpio objects */
#define NUMBER_OF_LEDS 					1u
/*! Index representing the LD2 USER LED on base Nucleo Board */
#define LD2_USER_LED_IDX 				0u
/*! Number of Blinky main cycle calls to toggle LED state if blinky */
#define BLINKY_CYCLE_MAIN_CYCLE_COUNT 	500UL

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Global Variables
*******************************************************************************/

/*! Declaration of Start Range for CRC calculation */
extern const uint32_t __START_CRC_FLASH[];

/*! Declaration of End Range for CRC calculation */
extern const uint32_t __END_CRC_FLASH[];

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Static Variables
*******************************************************************************/

static void CtorAll_RunState(RunState* const pThis)
{
    static DrvCrc m_drvCrc;

    static DrvCrcCfg m_drvCrcCfg =
    {
        .pHdma = &hdma_memtomem_dma1_channel1,
        .pHcrc = &hcrc,
        .dstAddress = (uint32_t) &CRC->DR,
        .isHardwareCrc = true,
        .crcRangeStartAddress = (const uint32_t)__START_CRC_FLASH,
        .crcRangeEndAddress = (const uint32_t)__END_CRC_FLASH,
        .pCrcAddress = (const uint32_t*)__END_CRC_FLASH
    };

    static RunStateConfig m_runStateCfg =
    {
        .pDrvCrc =  &m_drvCrc,
    };

    DrvCrc_Construct(&m_drvCrc, &m_drvCrcCfg);

    RunState_Construct(pThis, &m_runStateCfg);
}

static void CtorAll_WaitState(WaitState* const pThis)
{
    static DrvTimer m_waitStateTimer;

    static DrvTimerCfg m_waitStateTimerCfg =
    {
        .pTim = &htim1,

        .type = DrvTimer_UsTimer,

        .ticksPerSecond = 1000000UL,

        .waitTimeInit = 0UL,
    };

    DrvTimer_Construct(&m_waitStateTimer, &m_waitStateTimerCfg);

    static WaitStateCfg m_waitStateCfg =
    {
        .pDrvTimer = &m_waitStateTimer,
    };

    WaitState_Construct(pThis, &m_waitStateCfg);
}

/*******************************************************************************
* Functions
*******************************************************************************/

void CtorAll_Construct(MainState* const pThis)
{
    static RunState m_runState;

    static WaitState m_waitState;

    static MainStateConfig m_mainStateCfg =
    {
        .pRunState = &m_runState,
        .pWaitState = &m_waitState,
    };

    CtorAll_RunState(&m_runState);
    CtorAll_WaitState(&m_waitState);

    MainState_Construct(pThis, &m_mainStateCfg);
}
