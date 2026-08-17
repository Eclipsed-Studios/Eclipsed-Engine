#include "PathManager.h"
#include <iostream>

namespace Eclipse
{
	void PathManager::Init(const std::string& projectPath)
	{
		namespace fs = std::filesystem;

		engineSourceRoot = fs::current_path();
		projectRoot = fs::absolute(projectPath);
	}

	bool PathManager::ProjectSet()
	{
		return !projectRoot.empty();
	}
}