#pragma once

#include "Windows/ConsoleWindow.h"
#include "Windows/HierarchyWindow.h"
#include "Windows/InspectorWindow.h"
#include "Windows/AssetWindow.h"
#include "Windows/InputEditorWindow.h"

#include <unordered_map>

namespace ENGINE_NAMESPACE::Editor
{
	class WindowManager final
	{
	public:
		template<typename T>
		void OpenWindow(int aId);
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

	template<typename T>
	inline void WindowManager::OpenWindow(int aId)
	{
		AbstractWindow* window = nullptr;

		if constexpr(std::is_same<T, ConsoleWindow>::value)	window = new ConsoleWindow(aId);
		else if constexpr (std::is_same<T, HierarchyWindow>::value)	window = new HierarchyWindow(aId);
		else if constexpr (std::is_same<T, InspectorWindow>::value)	window = new InspectorWindow(aId);
		else if constexpr (std::is_same<T, AssetWindow>::value)	window = new AssetWindow(aId);
		else if constexpr (std::is_same<T, InputEditorWindow>::value)	window = new InputEditorWindow(aId);

		if (window == nullptr) return;

		window->Open();
		IdToWindow[window->GetID()] = window;
	}
}