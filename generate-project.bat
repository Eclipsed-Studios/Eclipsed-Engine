cmake -G "Visual Studio 17 2022" -T host=x64 -S . -B build

copy "Tools\DLLs\*.dll" "Bin\"

@REM attrib +h /s /d "build\*"
@REM attrib +h "build"

@REM set "root=."

@REM @echo off

@REM for /r "%root%" %%f in (CMakeLists.txt) do 
@REM (
@REM     if exist "%%f" 
@REM     (
@REM         attrib +h "%%f"
@REM         echo Hidden: %%f
@REM     ) 
@REM     else ()
@REM )