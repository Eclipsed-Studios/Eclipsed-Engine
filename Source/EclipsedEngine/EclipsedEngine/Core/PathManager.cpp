#include "PathManager.h"
#include <iostream>

namespace Eclipse
{
	void PathManager::Init()
	{
		namespace fs = std::filesystem;

		engineSourceRoot = fs::current_path();
	}

	void PathManager::SetProjectPath(const char* projectPath)
	{
		namespace fs = std::filesystem;
		projectRoot = fs::absolute(projectPath);
	}

	bool PathManager::ProjectSet()
	{
		return !projectRoot.empty();
	}
}