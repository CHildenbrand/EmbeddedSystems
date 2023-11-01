# project specific make file
TARGET = project

-include FileList.mak

-include CompilerFlags.mak

-include $(wildcard $(OBJ_DIR)/*.d)

Debug: PostProcess

$(OBJ_DIR)/%.o: %.c | PreProcess
	@echo Compiling $*.c...
	@$(CC) $(CFLAGS) -c $(filter %/$*.c, $(C_SOURCES)) -o $@

$(OBJ_DIR)/%.o: %.s | PreProcess
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

PreProcess: Directories
	@echo Preprocessing files...
	@py $(PRE_PROCESS) $(PROJECT_ROOT_PATH) $(ASTYLE)
	@$(DOXYGEN) $(DOXYFILE_PATH) 2>NUL

PostProcess: $(HEX_FILE)
	@$(POST_PROCESS) $(PROJECT_PATH) $< 0x00

Directories:
	@if not exist $(OUT_DIR) (@echo Parser: $(CC) -c $(CFLAGS) $< -o $@)
	@if not exist $(OUT_DIR) mkdir $(OUT_DIR) 
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

Clean:
	@if exist "target" (rmdir "target" /Q /S)
	@echo Workspace cleared!
