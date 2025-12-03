#pragma once

#include <string>

namespace Eclipse::Editor
{
	class EditorProjectManager
	{
	public:
		std::string LoadOrSelectProject();
		std::string LoadProjectFromFile();
		void SaveProjectPath(const std::string& path);
	};
}