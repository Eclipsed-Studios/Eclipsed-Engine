#include "MainSingleton.h"

namespace Eclipse::Utilities
{
	std::unordered_map<std::type_index, void *> MainSingleton::mySingletons;
	bool MainSingleton::myIsInitialized = false;

	void MainSingleton::Init()
	{
		
	}

	const bool &MainSingleton::IsSetup() { return myIsInitialized; }
}