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
		void DrawDebugInfoWindow();

		bool myShowDebugWindow = false;

	private:
		std::unordered_map<int, AbstractWindow*> IdToWindow;
	};
}