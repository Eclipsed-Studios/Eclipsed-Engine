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
    -B "%PROJECT_PATH%/Library/Game-Game-Building"  ^
    -DECLIPSED_EDITOR=OFF  ^
    -DINCLUDE_GAME=ON   ^
    -DBUILD_GAME_PATH="%PROJECT_PATH%" ^
    -DENABLE_NETWORKING="%ENABLE_NETWORKING%" ^
    -DENABLE_STEAM_SDK="%ENABLE_STEAM_SDK%" ^
    -DENABLE_DISCORD_SDK="%ENABLE_DISCORD_SDK%" ^
    -DCONFIG="%CONFIG%"



cd "%PROJECT_PATH%"

@REM call %PROJECT_PATH%/Tools/generate-game-build.bat %PROJECT_PATH%  %CURRENT_PATH%


cmake --build "%PROJECT_PATH%/Library/Game-Building-Binary" --config %CONFIG%

@REM copy /Y "%ENGINE_PATH%\Thirdparty\DLLs\*.*" "%PROJECT_PATH%\Build\"

set "SKIP_LIST="

if "%ENABLE_STEAM_SDK%"=="OFF" (
    for /f "delims=" %%f in ('dir /b "%ENGINE_PATH%\Thirdparty\DLLs\*steam*"') do (
        set "SKIP_LIST=!SKIP_LIST! %%f"
    )
)     

if "%ENABLE_DISCORD_SDK%"=="OFF" (
    for /f "delims=" %%f in ('dir /b "%ENGINE_PATH%\Thirdparty\DLLs\*discord*"') do (
        set "SKIP_LIST=!SKIP_LIST! %%f"
    )
)     

if defined SKIP_LIST (
    for /f "delims=" %%f in ('dir /s /b "%ENGINE_PATH%\Thirdparty\DLLs\*"') do (
        set "filename=%%~nxf"
        set "should_skip=0"
        
        for %%s in (!SKIP_LIST!) do (
            if "!filename!"=="%%s" set "should_skip=1"
        )
        
        if !should_skip! EQU 0 (
            set "relpath=%%f"
            set "relpath=!relpath:%ENGINE_PATH%\Thirdparty\DLLs\=!"
            
            copy /Y "%%f" "%PROJECT_PATH%\Build\" > nul
            echo Copied: !relpath!
        ) else (
            echo Skipped: !filename!
        )
    )
) else (
    xcopy "%ENGINE_PATH%\Thirdparty\DLLs\*" "%PROJECT_PATH%\Build\" /E /I /Y
)

xcopy "%PROJECT_PATH%\Project\Settings\*" "%PROJECT_PATH%\Build\" /E /I /Y