@echo off
setlocal enabledelayedexpansion

REM Initialize variables
set "PROJECT_PATH="
set "ENGINE_PATH="
set "CONFIG="

REM Parse command line arguments
:parse_args
if "%~1"=="" goto :done_parsing
if "%~1"=="-DPROJECT_PATH" (
    set "PROJECT_PATH=%~2"
    shift
    shift
    goto :parse_args
)
if "%~1"=="-DENGINE_PATH" (
    set "ENGINE_PATH=%~2"
    shift
    shift
    goto :parse_args
)
if "%~1"=="-DCONFIG" (
    set "CONFIG=%~2"
    shift
    shift
    goto :parse_args
)
shift
goto :parse_args

:done_parsing

REM Check if required variables are set
if not defined PROJECT_PATH (
    echo ERROR: -DPROJECT_PATH is required
    exit /b 1
)
if not defined ENGINE_PATH (
    echo ERROR: -DENGINE_PATH is required
    exit /b 1
)
if not defined CONFIG (
    echo ERROR: -DCONFIG is required
    exit /b 1
)

echo PROJECT_PATH=!PROJECT_PATH!
echo ENGINE_PATH=!ENGINE_PATH!
echo CONFIG=!CONFIG!

set "CURRENT_PATH=%cd%"

cmake -G "Visual Studio 18 2026" ^
    -T host=x64 ^
    -S ../ ^
    -B "!PROJECT_PATH!\Library\Game-Building-Binary" ^
    -DECLIPSED_EDITOR=OFF ^
    -DINCLUDE_GAME=ON ^
    -DBUILD_GAME_PATH="!PROJECT_PATH!"

if %errorlevel% neq 0 (
    echo CMake generation failed!
    exit /b %errorlevel%
)

cd "!PROJECT_PATH!"

if exist "!PROJECT_PATH!\Tools\generate-game-build.bat" (
    call "!PROJECT_PATH!\Tools\generate-game-build.bat" "!PROJECT_PATH!" "!CURRENT_PATH!"
) else (
    echo WARNING: generate-game-build.bat not found
)

cmake --build "!PROJECT_PATH!\Library\Game-Building-Binary" --config !CONFIG!

if exist "!ENGINE_PATH!\Thirdparty\DLLs\*.*" (
    copy /Y "!ENGINE_PATH!\Thirdparty\DLLs\*.*" "!PROJECT_PATH!\Build\"
) else (
    echo WARNING: DLLs directory not found
)

endlocal

if %errorlevel% equ 0 (
    echo Build completed successfully!
    exit /b 0
) else (
    echo Build failed with error code: %errorlevel%
    exit /b %errorlevel%
)