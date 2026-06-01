@echo off

setlocal

echo === Begun: Copying extra files ===

xcopy "Thirdparty/etc\*" "Bin" /E /I /Y

echo === Completed: Copying extra files
endlocal