@echo off




@REM Generate cmake

echo %2

@REM cmake -G "Visual Studio 17 2022"                ^
@REM     -T host=x64                                 ^
@REM     -S %2                                       ^
@REM     -B %2/Libary/Game-Build                     ^
@REM     -DBUILD_GAME=ON

cmake -G "Visual Studio 17 2022"                ^
    -T host=x64                                 ^
    -S ./Eclipse-Source/                        ^
    -B ./Eclipse-Source/Library/Game-Build      ^
    -DECLIPSED_EDITOR=OFF                       ^
    -DINCLUDE_GAME=ON                           ^
    -DBUILD_GAME=ON                             ^
    -DEXE_OUTPUT_DIR=%1 


@REM cd ..
cd Eclipse-Source

xcopy "Assets/DLLs\*" %1 /E /I /Y