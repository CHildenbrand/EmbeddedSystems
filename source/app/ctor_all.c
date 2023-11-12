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
    static DrvBlinky m_drvBlinky;

    static DrvCrc m_drvCrc;

    static DrvTimer m_drvTimer;

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

    static DrvTimerCfg m_drvTimerCfg =
    {
        .pTim = &htim20,
        .type = DrvTimer_EncoderAB,
        .ticksPerSecond = 0UL,
        .waitTimeInit = 0UL,
    };

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

    static RunStateConfig m_runStateCfg =
    {
        .pDrvBlinky =  &m_drvBlinky,
        .pDrvCrc =  &m_drvCrc,
        .pEncoderAB = &m_drvTimer,
    };

    DrvTimer_Construct(&m_drvTimer, &m_drvTimerCfg);

    DrvCrc_Construct(&m_drvCrc, &m_drvCrcCfg);

    DrvBlinky_Construct(&m_drvBlinky, &m_drvBlinkyCfg);

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
