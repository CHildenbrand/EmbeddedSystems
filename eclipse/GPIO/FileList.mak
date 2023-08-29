

# List of Paths and Binary files
OBJ_DIR = target\obj
OUT_DIR = target\out

ELF_FILE = $(OUT_DIR)/$(TARGET).elf
HEX_FILE = $(OUT_DIR)/$(TARGET).hex
BIN_FILE = $(OUT_DIR)/$(TARGET).bin


# List of Source Files and Include Files
C_SOURCES = ../../source/app/main.c \
		../../source/app/main_state.c \
		../../CubeMx/Core/Src/gpio.c \
		../../CubeMx/Core/Src/stm32g4xx_hal_msp.c \
		../../CubeMx/Core/Src/stm32g4xx_it.c \
		../../CubeMx/Core/Src/system_stm32g4xx.c \
		../../CubeMx/Core/Src/tim.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c

ASM_SOURCES = ../../CubeMx/startup_stm32g474xx.s

INCLUDE_DIR = ../../CubeMx/Core/Inc \
		../../CubeMx/Drivers/CMSIS/Device/ST/STM32G4xx/Include \
		../../CubeMx/Drivers/CMSIS/Include \
		../../CubeMx/Drivers/STM32G4xx_HAL_Driver/Inc \
		../../source/app

LDSCRIPT = ../../source/lib/STM32G474RETx_FLASH.ld

VPATH += $(sort $(dir $(C_SOURCES)))
VPATH += $(sort $(dir $(ASM_SOURCES)))

INCLUDES = $(addprefix -I, $(INCLUDE_DIR))

OBJ_FILES += $(addprefix $(OBJ_DIR)/,$(notdir $(C_SOURCES:.c=.o))) 
OBJ_FILES += $(addprefix $(OBJ_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
OBJS = $(sort $(OBJ_FILES))