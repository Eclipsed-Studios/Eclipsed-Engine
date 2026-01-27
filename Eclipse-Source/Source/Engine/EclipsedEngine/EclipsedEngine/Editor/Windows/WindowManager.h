#pragma once

#include <unordered_map>

#include "WindowRegistry.h"

namespace Eclipse::Editor
{


	class WindowManager final
	{
	public:
		void OpenWindow(const std::string& name, int aId);

		void UpdateMainMenuBar();

		void Update();

		void Begin();
		void End();

		void AddWindowToCategory(const std::vector<std::string>& categories, size_t idx, const std::string& windowName);

	private:
		void OpenLayout(const char* aName);
		void ExportLayout();
		void ImportLayout();
		void SaveLayoutToMemory();

		bool myShowDebugWindow = false;

	private:
		std::unordered_map<std::string, std::string> myLayouts = 
		{
			{"Default", "{\"OpenWindows\":[{\"id\":0,\"name\":\"Inspector\"},{\"id\":1,\"name\":\"Game\"},{\"id\":2,\"name\":\"Scene\"},{\"id\":3,\"name\":\"Assets\"},{\"id\":3,\"name\":\"Console\"},{\"id\":-4,\"name\":\"Hierarchy\"}]}"}
		};
		std::unordered_map<int, AbstractWindow*> IdToWindow;
	};
}