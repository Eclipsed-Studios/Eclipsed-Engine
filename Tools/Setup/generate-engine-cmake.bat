@echo off

setlocal

echo === Begun: Generate engine cmake ===

cmake -G "Visual Studio 18 2026"                 ^
    -T host=x64  ^
    -S .  ^
    -B Temp/Binary  ^
    -DECLIPSED_EDITOR=ON  ^
    -DINCLUDE_GAME=OFF   ^
    -DBUILD_GAME_PATH="${CMAKE_SOURCE_DIR}/Bin" ^
    -DENABLE_NETWORKING="ON" ^
    -DENABLE_STEAM_API="ON"

echo === Completed: Generate engine cmake ===

endlocal