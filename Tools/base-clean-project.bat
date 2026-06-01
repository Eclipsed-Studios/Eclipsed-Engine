@echo off

if exist "Bin" (
    echo Deleting "Bin" directory
    rd /s /q "Bin"
)

if exist "Temp" (
    echo Deleting "Temp" directory
    rd /s /q "Temp"
)

:wait
taskkill /im devenv.exe
timeout /t 1 /nobreak >nul
tasklist /fi "imagename eq devenv.exe" | find /i "devenv.exe" >nul
if not errorlevel 1 goto wait

if exist ".vs" (
    echo Deleting ".vs" directory
    rd /s /q ".vs"
)

if exist "Eclipsed-Engine.slnx" (
    echo Deleting "Eclipsed-Engine.slnx" file
    del Eclipsed-Engine.slnx
)

if exist "x64" (
    echo Deleting "x64" directory
    rd /s /q "x64"
)
