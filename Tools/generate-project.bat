@echo off

cmake -G "Visual Studio 17 2022" -T host=x64 -S ../Eclipse-Source/ -B ../Eclipse-Source/build

rem Hide the build folder.
attrib +h "../Eclipse-Source/build"