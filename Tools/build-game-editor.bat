@echo off

setlocal


set "PROJECT_PATH=%~1"
set "ENGINE_PATH=%~2"

set "CURRENT_PATH=%cd%"

cmake -G "Visual Studio 18 2026"                 ^
    -T host=x64  ^
    -S ../  ^
    -B "%PROJECT_PATH%/Library/Game-Building-Binary"  ^
    -DECLIPSED_EDITOR=OFF  ^
    -DINCLUDE_GAME=ON   ^
    -DBUILD_GAME_PATH="%PROJECT_PATH%"



cd "%PROJECT_PATH%"

call %PROJECT_PATH%/Tools/generate-game-build.bat %PROJECT_PATH%  %CURRENT_PATH%


cmake --build "%PROJECT_PATH%/Library/Game-Building-Binary" --config %3

copy /Y "%ENGINE_PATH%\Thirdparty\DLLs\*.*" "%PROJECT_PATH%\Build\"



endlocal


if %errorlevel% equ 0 (
    @REM exit 
) else (
    echo Build failed!
)