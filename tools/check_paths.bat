
REM Check Availablity of Paths
@if not exist %TOOLS_PATH% (
    @echo Path: %TOOLS_PATH% does not exist!
    @echo Adust either the Enviroment Variable TOOLS_PATH or relocate installation folder of tools!
    @set errorlevel=1
)

@if not exist %ECLIPSE_ROOT_PATH% (
    @echo Path: %ECLIPSE_ROOT_PATH% does not exist!
    @echo Adjust either env variable or relocate Eclipse installation!
    @set errorlevel=2
)

REM Check Availablity of Prebuild Tools
@if not exist %ASTYLE_ROOT_PATH% (
    @echo Path: %ASTYLE_ROOT_PATH% does not exist!
    @echo Adjust either env variable or relocate astyle installation folder!
    @set errorlevel=3
)

@if not exist %DOXYGEN_PATH% (
    @echo Path: %DOXYGEN_PATH% does not exist!
    @echo Adjust either env variable or relocate Doxygen installation folder!
    @set errorlevel=4
)

REM Check Availablity of Build and Debug Tools
@if not exist %MAKE_ROOT_PATH% (
    @echo Path: %MAKE_ROOT_PATH% does not exist!
    @echo Adjust either env variable or relocate Make installation folder!
    @set errorlevel=6
)

@if not exist %OPENOCD_PATH% (
    @echo Path: %OPENOCD_PATH% does not exist!
    @echo Adjust either env variable or relocate OpenOCD installation folder!
    @set errorlevel=7
)

@if not exist %COMPILER_ROOT_PATH% (
    @echo Path: %COMPILER_ROOT_PATH% does not exist!
    @echo Adjust either env variable or relocate Compiler installation folder!
    @set errorlevel=5
)
