@echo off
@echo Post Process Hex-File

pushd

py %~dp0.\post_process.py %~1 %~2 %~3

popd
