# project specific make file
TARGET = project

-include FileList.mak

-include CompilerFlags.mak

-include $(wildcard $(OBJ_DIR)/*.d)

Debug: $(ELF_FILE) $(HEX_FILE)

$(OBJ_DIR)/%.o: %.c | Directories
	@echo Compiling $*.c...
	$(CC) $(CFLAGS) -c $(filter %/$*.c, $(C_SOURCES)) -o $@

#Add Line 17 to Line 15 to show preprocessor output
#$(CC) $(CFLAGS) -E -dN -c $(filter %/$*.c, $(C_SOURCES)) -o ${OBJ_DIR}/$*.pp

$(OBJ_DIR)/%.o: %.s | Directories
	@echo Assembling $*.c...
	$(CC) $(ASFLAGS) -c $(filter %/$*.s, $(ASM_SOURCES)) -o $@

$(OUT_DIR)/$(TARGET).elf: $(OBJS)
	@echo Linking $(notdir $@)...
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	@echo Display sizes...
	$(SZ) $@

$(OUT_DIR)/%.hex: $(OUT_DIR)/%.elf
	@echo Generating $(notdir $@)...
	$(CP) -O ihex $< $@
		
$(OUT_DIR)/%.bin: $(OUT_DIR)/$(TARGET).elf
	@echo Generating binary $(notdir $@)...
	$(CP) -O binary $< $@

Directories:
	@if not exist $(OUT_DIR) (@echo Parser: $(CC) -c $(CFLAGS) $< -o $@)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR) 
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

Clean:
	@if exist "target" (rmdir "target" /Q /S)
	@echo Workspace cleared!
