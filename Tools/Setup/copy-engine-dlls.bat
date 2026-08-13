@echo off

setlocal

xcopy "Thirdparty/DLLs\*" "Bin" /E /I /Y >nul 2>&1

endlocal