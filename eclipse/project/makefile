# project specific make file
TARGET = project

-include FileList.mak

-include CompilerFlags.mak

-include $(wildcard $(OBJ_DIR)/*.d)

Build: PostBuild

$(OBJ_DIR)/%.o: %.c | PreBuild
	@echo Compiling $*.c...
	@$(CC) $(CFLAGS) -c $(filter %/$*.c, $(C_SOURCES)) -o $@

$(OBJ_DIR)/%.o: %.s | PreBuild
	@echo Assembling $*.s...
	@$(CC) $(ASFLAGS) -c $(filter %/$*.s, $(ASM_SOURCES)) -o $@

$(ELF_FILE): $(OBJS)
	@echo Linking $(notdir $@)...
	@$(LD) $(OBJS) $(LDFLAGS) -o $@
	@echo Display sizes...
	@$(SZ) $@

$(HEX_FILE): $(ELF_FILE)
	@echo Generating Hex-File $(notdir $@)...
	@$(CP) -O ihex $< $@

# $(PRE_PROCESS): --verbose as 4th parameter outputs the list of processed files

PreBuild: Directories
	@echo Preprocessing files...
	@$(PRE_PROCESS) $(PROJECT_ROOT_PATH) $(ASTYLE) $(ASTYLE_CFG_PATH)
	@$(DOXYGEN) $(DOXYFILE_PATH)

# $(POST_PROCESS): --verbose as 2nd parameter outputs value and address of crc

PostBuild: $(HEX_FILE)
	@echo Postprocessing files...
	@$(POST_PROCESS) $(PROJECT_PATH) $<

Directories:
	@if not exist $(OUT_DIR) (@echo arm-none-eabi-gcc $(CFLAGS) -c main.c -o main.o)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR) 
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

Clean:
	@if exist "target" (rmdir "target" /Q /S)
	@echo Workspace cleared!
