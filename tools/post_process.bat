@echo off
@echo Post Process Hex-File

py %~dp0.\post_process.py %~1 %~2

popd