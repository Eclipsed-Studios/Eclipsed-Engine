#include "MainSingleton.h"

namespace ENGINE_NAMESPACE::Utilities
{
	std::unordered_map<std::type_index, void*> MainSingleton::mySingletons;
	bool MainSingleton::myIsInitialized = false;

	void MainSingleton::Init()
	{
	}

	const bool& MainSingleton::IsSetup() { return myIsInitialized; }
}