@echo off
pushd

set "PROJECT_NAME=GPIO"

REM Set Toolchain Paths
@echo Set root paths...
set "TOOLS_PATH=C:\Tools"
set "ECLIPSE_ROOT_PATH=%TOOLS_PATH%\eclipse"
set "COMPILER_ROOT_PATH=%TOOLS_PATH%\ArmGnuToolchain\bin"
set "ASTYLE_ROOT_PATH=%TOOLS_PATH%\Astyle"
set "MAKE_ROOT_PATH=%TOOLS_PATH%\MinGW\bin"
set "OPENOCD_PATH=%TOOLS_PATH%\openocd\bin"

@echo Set execution paths...
set "ECLIPSE=%ECLIPSE_ROOT_PATH%\eclipse.exe"
set "CC=%COMPILER_ROOT_PATH%\arm-none-eabi-gcc.exe"
set "CP=%COMPILER_ROOT_PATH%\arm-none-eabi-objcopy.exe"
set "SZ=%COMPILER_ROOT_PATH%\arm-none-eabi-size.exe"
set "GDB=%COMPILER_ROOT_PATH%\arm-none-eabi-gdb.exe"
set "ASTYLE=%ASTYLE_ROOT_PATH%\astyle.exe"
set "MAKE_EXE=%MAKE_ROOT_PATH%\mingw32-make.exe"
set "OPENOCD=%OPENOCD_PATH%\openocd.exe"

REM Set Project Paths
@echo Set project paths...
set "PROJECT_ROOT_PATH=%cd%"
set "WORKSPACE_PATH=%PROJECT_ROOT_PATH%\eclipse"
set "PROJECT_PATH=%WORKSPACE_PATH%\%PROJECT_NAME%"
set "SVD_FILE_PATH=%PROJECT_ROOT_PATH%\source\lib\STM32G474xx.svd"

REM Add root paths to PATH enviroment variables

if not exist %WORKSPACE_PATH%\.metadata (
	@echo Import eclipse project %PROJECT_NAME% in workspace at %WORKSPACE_PATH%
	%ECLIPSE% -nosplash -no-indexer -application org.eclipse.cdt.managedbuilder.core.headlessbuild -import "%PROJECT_PATH%" -data "%WORKSPACE_PATH%"
) 

@echo Open eclipse project %PROJECT_NAME%
start %ECLIPSE% -data %WORKSPACE_PATH%

popd
exit %errorlevel%