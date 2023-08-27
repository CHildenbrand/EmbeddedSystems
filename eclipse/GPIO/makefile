# project specific make file
TARGET = gpio_led_on

-include FileList.mak

-include CompilerFlags.mak

-include $(wildcard $(OBJ_DIR)/*.d)

Debug: $(ELF_FILE) $(HEX_FILE)

$(OBJ_DIR)/%.o: %.c | Directories
	@echo Compiling $*.c ...
	$(CC) $(CFLAGS) -c $(filter %/$*.c, $(C_SOURCES)) -o $@

#$(CC) $(CFLAGS) -E -dN -c $(filter %/$*.c, $(C_SOURCES)) -o target/obj/$*.pp

$(OBJ_DIR)/%.o: %.s | Directories
	@echo Assembling $*.c ...
	@$(AS) $(ASFLAGS) -c $(filter %/$*.s, $(ASM_SOURCES)) -o $@

$(OUT_DIR)/$(TARGET).elf: $(OBJS)
	@echo Linking $(notdir $@) ...
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	@$(SZ) $@
	
$(OUT_DIR)/%.hex: $(OUT_DIR)/%.elf
	@echo Generating Hex-File $(notdir $@) ...
	@$(CP) -O ihex $< $@
		
$(OUT_DIR)/%.bin: $(OUT_DIR)/$(TARGET).elf
	@echo Generating Binary-File $(notdir $@) ...
	@$(CP) -O binary $< $@
	
Directories:
	@if not exist $(OUT_DIR) (@echo Parser: $(CC) -c $(CFLAGS) $< -o $@)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR) 
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@echo Output directories created!

$(OUT_FILES_PATH)/$(TARGET).elf: $(OBJS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@
	
Clean:
	@if exist "target" (rmdir "target" /Q /S)
	@echo Workspace cleared!
	