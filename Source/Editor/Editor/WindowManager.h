#pragma once

#include "Windows/ConsoleWindow.h"

#include <unordered_map>

namespace ENGINE_NAMESPACE::Editor
{
	class WindowManager final
	{
	public:
		template<typename T>
		void OpenWindow(int aId);

		void UpdateMainMenuBar();

		void Save();
		void Update();

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

		if (std::is_same<T, ConsoleWindow>::value)	window = new ConsoleWindow(aId);

		if (window == nullptr) return;

		window->Open();
		IdToWindow[window->GetID()] = window;
	}
}