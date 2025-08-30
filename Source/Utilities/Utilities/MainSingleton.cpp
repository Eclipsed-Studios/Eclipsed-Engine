#include "MainSingleton.h"

namespace Zultools
{
	std::unordered_map<std::string, void*> MainSingleton::mySingletons;
	bool MainSingleton::myIsInitialized = false;

	void MainSingleton::Init()
	{
	}

	const bool& MainSingleton::IsSetup() { return myIsInitialized; }
}