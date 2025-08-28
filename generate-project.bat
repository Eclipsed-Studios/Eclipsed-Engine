cmake -G "Visual Studio 17 2022" -T host=x64 -S . -B build

attrib +h /s /d "build\*"
attrib +h "build"

set "root=."

@echo off

for /r "%root%" %%f in (CMakeLists.txt) do 
(
    if exist "%%f" 
    (
        attrib +h "%%f"
        echo Hidden: %%f
    ) 
    else ()
)