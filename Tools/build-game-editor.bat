@echo OFF

setlocal enabledelayedexpansion

:parse-arg
if "%~1"=="" goto :end
for /f "tokens=1,* delims==" %%A in ("%~1") do (
    set "%%A=%%B"
)

shift
goto parse-arg
:end


set "CURRENT_PATH=%cd%"

cmake -G "Visual Studio 18 2026"                 ^
    -T host=x64  ^
    -S ../  ^
    -B "%PROJECT_PATH%/Library/Game-Building-Binary"  ^
    -DECLIPSED_EDITOR=OFF  ^
    -DINCLUDE_GAME=ON   ^
    -DBUILD_GAME_PATH="%PROJECT_PATH%" ^
    -DENABLE_NETWORKING="%ENABLE_NETWORKING%" ^
    -DENABLE_STEAM_API="%ENABLE_STEAM_API%"



cd "%PROJECT_PATH%"

call %PROJECT_PATH%/Tools/generate-game-build.bat %PROJECT_PATH%  %CURRENT_PATH%


cmake --build "%PROJECT_PATH%/Library/Game-Building-Binary" --config %CONFIG%

copy /Y "%ENGINE_PATH%\Thirdparty\DLLs\*.*" "%PROJECT_PATH%\Build\"



endlocal


if %errorlevel% equ 0 (
    @REM exit 
) else (
    echo Build failed!
)