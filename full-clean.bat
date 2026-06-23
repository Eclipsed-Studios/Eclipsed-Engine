@echo off

setlocal

echo === Begun: Performing Full Cleaning Off Project ===
echo.

call Tools/base-clean-project.bat

cd Source/Externals

if exist steamsdk (
    echo Deleting "steamsdk" directory
    rd /s /q steamsdk
)

echo.
echo === Completed: Cleaning project ===

endlocal 