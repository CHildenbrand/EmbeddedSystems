# List of arm-none-eabi-gcc generic compiler settings
CPU = STM32G474

OPTIMIZATION = -O0 -g3 -ggdb

MCU += -D$(CPU)
MCU += -mcpu=cortex-m4
MCU += -mfloat-abi=hard
MCU += -mfpu=fpv4-sp-d16
MCU += -DCPU=$(CPU)
MCU += -D$(CPU)xx

ASFLAGS += $(MCU)
ASFLAGS += $(INCLUDES)
ASFLAGS += $(OPTIMIZATION)
ASFLAGS += -Wall 
ASFLAGS += -fdata-sections
ASFLAGS += -ffunction-sections
ASFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

CFLAGS += $(MCU)
CFLAGS += $(INCLUDES)
CFLAGS += $(OPTIMIZATION)
CFLAGS += -DUSE_HAL_DRIVER 
CFLAGS += -Wall 
CFLAGS += -fdata-sections 
CFLAGS += -ffunction-sections
CFLAGS += --specs=rdimon.specs
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

LDFLAGS += -g3 -ggdb
LDFLAGS += $(MCU)
LDFLAGS += -T$(LDSCRIPT) 
LDFLAGS += -Wl,-Map=$(OUT_DIR)/$(TARGET).map
LDFLAGS += -Wl,--cref,--gc-sections,--no-warn-rwx-segments

AS = $(CC) -x assembler-with-cpp
