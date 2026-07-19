@echo off

setlocal

echo === Begun: Generate engine cmake ===

cmake -G "Visual Studio 18 2026"                 ^
    -T host=x64                                  ^
    -S .                                        ^
    -B Temp/Binary                              ^
    -DECLIPSED_EDITOR=ON                        ^
    -DINCLUDE_GAME=OFF                          ^
    -DBUILD_GAME_PATH="%CD%/Bin"                ^
    -DENABLE_NETWORKING="ON"                    ^
    -DENABLE_STEAM_API="ON"                     ^
    -DCMAKE_INSTALL_PREFIX="%CD%/Temp/Install"


if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%


echo === Building engine ===

cmake --build Temp/Binary --config Debug


if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%


echo === Installing engine ===

cmake --install Temp/Binary --config Debug


if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%


echo === Completed: Generate engine cmake ===

endlocal