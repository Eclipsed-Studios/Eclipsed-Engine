#include "MainSingleton.h"

#include <Zultools/Timer.h>

namespace Zultools
{
	std::unordered_map<std::string, void*> MainSingleton::mySingletons;
	bool MainSingleton::myIsInitialized = false;

	void MainSingleton::Init()
	{
		RegisterInstance<CommonUtilities::Timer>();
	}

	const bool& MainSingleton::IsSetup() { return myIsInitialized; }
}