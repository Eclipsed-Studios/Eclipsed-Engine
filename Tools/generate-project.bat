@echo off

cmake -G "Visual Studio 17 2022" -T host=x64 -S ../Eclipse-Source/ -B ../Eclipse-Source/Library/Binary -DECLIPSED_EDITOR=ON
    
cd ..
cd Eclipse-Source

xcopy "Assets/DLLs\*" "Bin" /E /I /Y
xcopy "Assets/EngineAssets" "Bin/EngineAssets" /E /I /Y

set SOURCE=Source
set DEST=Bin/Headers

robocopy "%SOURCE%" "%DEST%" *.h *.inl *.hpp /S /E /R:0 /W:0


pause
@REM rem Hide the build folder.
@REM attrib +h "../Eclipse-Source/build"