@echo off
pushd
cd %~dp0..

set "PROJECT_NAME=GPIO"

REM Set environment variables
@echo Set enviroment variables...
set "ARM_NONE_EABI_ROOT_PATH=C:\Tools\ArmGnuToolchain\bin"
set "ASTYLE_ROOT_PATH=C:\Tools\Astyle"
set "MAKE_ROOT_PATH=C:\Tools\MinGW\bin"
set "OPENOCD_PATH=C:\Tools\openocd\bin"
set "ECLIPSE_EXE_PATH=C:\Tools\eclipse\eclipse.exe"

set "PROJECT_ROOT_PATH=%cd%"
set "WORKSPACE_PATH=%PROJECT_ROOT_PATH%\eclipse"
set "PROJECT_PATH=%WORKSPACE_PATH%\%PROJECT_NAME%"
set "SVD_FILE_PATH=%PROJECT_ROOT_PATH%\source\lib\STM32G474xx.svd"

REM Add root paths to PATH enviroment variables
set "PATH=%ARM_NONE_EABI_ROOT_PATH%;%ASTYLE_ROOT_PATH%;%MAKE_ROOT_PATH%;%PATH%"

if not exist %WORKSPACE_PATH%\.metadata (
	@echo Import eclipse project %PROJECT_NAME% in workspace at %WORKSPACE_PATH%
	%ECLIPSE_EXE_PATH% -nosplash -no-indexer -application org.eclipse.cdt.managedbuilder.core.headlessbuild -import "%PROJECT_PATH%" -data "%WORKSPACE_PATH%"
) 

@echo Open eclipse project %PROJECT_NAME%
start %ECLIPSE_EXE_PATH% -data %WORKSPACE_PATH%

popd
exit %errorlevel%