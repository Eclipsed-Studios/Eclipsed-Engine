#pragma once

#include <unordered_map>

#include "WindowRegistry.h"

namespace Eclipse::Editor
{
	class WindowManager final
	{
	public:
		void LoadLayouts();

		void OpenWindow(const std::string& name, int aId);

		void UpdateMainMenuBar();

		void Update();

		void Begin();
		void End();

		void AddWindowToCategory(const std::vector<std::string>& categories, size_t idx, const std::string& windowName);

	private:
		void OpenLayout(const char* aName);

		void DrawDebugInfoWindow();

		bool myShowDebugWindow = false;

	private:
		std::vector<std::string> myLayouts;
		const std::vector<std::string> Default_Layouts = { "Default" };
		std::unordered_map<int, AbstractWindow*> IdToWindow;
	};
}