@echo off
set errorlevel=0
set "PROJECT_NAME=project"
pushd 

call tools/set_env.bat
@if not errorlevel 0 goto Wrong_Env_Set

call tools/set_proj.bat
@if not errorlevel 0 goto Wrong_Proj_Set

call tools/check_paths.bat
@if not errorlevel 0 goto Wrong_Paths

@echo on
call tools/check_versions.bat
@if not errorlevel 0 goto Wrong_Versions

call tools/start_eclipse_clean.bat
@if not errorlevel 0 goto Wrong_Start_Eclipse

@popd
@goto Start_Eclipse_Successful

:Wrong_Paths
@echo check_paths.bat with errors!
pause 
exit 1

:Wrong_Versions
@echo check_versions.bat with errors!
pause
exit 4

:Wrong_Start_Eclipse
@echo start_eclipse_clean.bat with errors!
pause
exit 5

:Start_Eclipse_Successful
@echo Start of Eclipse was succesful!