#include "EditorProjectManager.h"

#include "Utilities/Files/FileUtilities.h"

namespace Eclipse::Editor
{
	std::string EditorProjectManager::LoadOrSelectProject()
	{
        namespace fs = std::filesystem;

        std::string path;
        if (fs::exists(".ini")) return LoadProjectFromFile();
        else path = Files::SelectFolderDialog();

        SaveProjectPath(path);
        return path;
	}

	std::string EditorProjectManager::LoadProjectFromFile()
	{
        std::ifstream in(".ini");
        std::string path;
        std::getline(in, path);

        in.close();
        return path;
	}

	void EditorProjectManager::SaveProjectPath(const std::string& path)
	{
        std::ofstream out(".ini", std::ios::trunc);
        out.write(path.c_str(), path.size());
        out.close();
	}
}