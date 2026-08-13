@echo off

setlocal

xcopy "Thirdparty/etc\*" "Bin" /E /I /Y >nul 2>&1

endlocal