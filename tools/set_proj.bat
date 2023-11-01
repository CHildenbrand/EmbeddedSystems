
REM Set Project Paths
@echo Set Project Paths...
set "PROJECT_ROOT_PATH=%cd%"
set "WORKSPACE_PATH=%PROJECT_ROOT_PATH%\eclipse"
set "PROJECT_PATH=%WORKSPACE_PATH%\%PROJECT_NAME%"
set "SVD_FILE_PATH=%PROJECT_ROOT_PATH%\source\lib\STM32G474xx.svd"
set "PRE_PROCESS=%PROJECT_ROOT_PATH%\tools\pre_process.exe"
set "POST_PROCESS=%PROJECT_ROOT_PATH%\tools\post_process.exe"
set "ASTYLE_CFG_PATH=%PROJECT_ROOT_PATH%\tools\Astylefile.txt"
set "DOXYFILE_PATH=%PROJECT_ROOT_PATH%\tools\Doxyfile.txt"