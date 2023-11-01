@echo off
set errorlevel=0
set "PROJECT_NAME=project"
pushd 

call tools/set_env.bat

call tools/set_proj.bat

call tools/check_paths.bat
if %errorlevel% neq 0 goto Wrong_Paths

call tools/check_versions.bat
if %errorlevel% neq 0 goto Wrong_Versions

call tools/start_eclipse_clean.bat
if %errorlevel% neq 0 goto Wrong_Start_Eclipse

@popd
@goto Start_Eclipse_Successful

:Wrong_Paths
@echo check_paths.bat with errors!
set errorlevel=1
pause
goto :eof

:Wrong_Versions
@echo check_versions.bat with errors!
set errorlevel=2
pause
goto :eof

:Wrong_Start_Eclipse
@echo start_eclipse_clean.bat with errors!
set errorlevel=3
pause
goto :eof

:Start_Eclipse_Successful
@echo Start of Eclipse was succesful!