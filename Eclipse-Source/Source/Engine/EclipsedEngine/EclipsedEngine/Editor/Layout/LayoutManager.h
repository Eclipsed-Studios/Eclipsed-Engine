#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

#include <filesystem>

#include "CoreEngine/Settings/SettingsModels/EditorLayout.h"

namespace Eclipse::Editor
{ 
	struct LayoutWindowData {
		int id;
		std::string name;
	};

	class LayoutManager
	{
	public:
		static std::vector<LayoutWindowData> OpenLayout(const std::string_view& layoutName);

		static void ImportLayout();
		static void SaveLayout();
		static void SaveAsNewLayout();
		static void SaveLayout(const std::string& name);

		static void Update();

		static void LoadLayouts();

		static const std::vector<std::string>& GetLayouts();

	private:
		static std::filesystem::path GetLayoutPath(const std::string& filename);

	private:
		static bool myOpenNameSelectPopup;
		static char myNameSelectBuffer[128];

		static std::vector<std::string> myLayouts;
	};
}