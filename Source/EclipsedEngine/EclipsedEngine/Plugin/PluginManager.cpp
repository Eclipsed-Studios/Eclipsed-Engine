#include "PluginManager.h"

#include "EclipsedEngine/Core/BatchScript.h"
#include "EclipsedEngine/Core/PathManager.h"

#include <fstream>
#include <iostream>
#include <Windows.h>

namespace Eclipse
{
	void PluginManager::Compile(const char* source)
	{
		Plugin* plug = new Plugin(source);
		if (!plug->Succeded())
		{
			delete plug;
			return;
		}

		loadedplugins[plug->GetName()] = plug;
		plug->GetInitFunc()();
	}
}