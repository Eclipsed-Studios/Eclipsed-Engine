#include "C:/Projects/Eclipsed/Eclipsed-Engine/Eclipse-Source/build/Source/Engine/Modules/CoreEngine/CMakeFiles/CoreEngine.dir/Debug/cmake_pch.hxx"

void Eclipse::MainSingleton::Destroy()
{
	for (auto& [type, singleton] : mySingletons)
	{
		singleton.deleter(singleton.instance);
	}
}
