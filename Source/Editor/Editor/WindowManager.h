#pragma once

#include "Windows/ConsoleWindow.h"
#include "Windows/HierarchyWindow.h"
#include "Windows/InspectorWindow.h"
#include "Windows/AssetWindow.h"
#include "Windows/InputEditorWindow.h"

#include <unordered_map>

#include "WindowRegistry.h"

namespace ENGINE_NAMESPACE::Editor
{
	class WindowManager final
	{
	public:
		void OpenWindow(const std::string& name, int aId);

		void UpdateMainMenuBar();

		void Update();

		void Begin();
		void End();

	private:
		void DrawDebugInfoWindow();

		bool myShowDebugWindow = false;

	private:
		std::unordered_map<int, AbstractWindow*> IdToWindow;
	};
}