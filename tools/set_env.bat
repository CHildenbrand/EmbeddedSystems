
REM Set Toolchain Paths
@echo Set Root Paths of Tools...
set "TOOLS_PATH=C:\Tools"
set "ECLIPSE_ROOT_PATH=%TOOLS_PATH%\eclipse"
set "COMPILER_ROOT_PATH=%TOOLS_PATH%\ArmGnuToolchain\bin"
set "ASTYLE_ROOT_PATH=%TOOLS_PATH%\Astyle"
set "MAKE_ROOT_PATH=%TOOLS_PATH%\MinGW\bin"
set "OPENOCD_PATH=%TOOLS_PATH%\openocd\bin"
set "DOXYGEN_PATH=%TOOLS_PATH%\doxygen\bin"

@echo Set Absolute Path to Tool Binaries...
set "ECLIPSE=%ECLIPSE_ROOT_PATH%\eclipse.exe"
set "CC=%COMPILER_ROOT_PATH%\arm-none-eabi-gcc.exe"
set "LD=%COMPILER_ROOT_PATH%\arm-none-eabi-gcc.exe"
set "CP=%COMPILER_ROOT_PATH%\arm-none-eabi-objcopy.exe"
set "SZ=%COMPILER_ROOT_PATH%\arm-none-eabi-size.exe"
set "GDB=%COMPILER_ROOT_PATH%\arm-none-eabi-gdb.exe"
set "ASTYLE=%ASTYLE_ROOT_PATH%\astyle.exe"
set "MAKE_EXE=%MAKE_ROOT_PATH%\mingw32-make.exe"
set "OPENOCD=%OPENOCD_PATH%\openocd.exe"
set "DOXYGEN=%DOXYGEN_PATH%\doxygen.exe"
