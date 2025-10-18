@echo off

cmake -G "Visual Studio 17 2022" -T host=x64 -S ../Eclipse-Source/ -B ../Eclipse-Source/build -DEDITOR=ON
      
      


pause
@REM rem Hide the build folder.
@REM attrib +h "../Eclipse-Source/build"