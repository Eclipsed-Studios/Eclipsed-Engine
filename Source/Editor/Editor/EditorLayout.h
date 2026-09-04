#pragma once

#include "Views/EditorViewRegistry.h"

#include "ImGui/imgui_internal.h"
#include <vector>

namespace Eclipse::Editor
{
	class EditorLayout
	{
	public:
		static void Init();

		static void EndFrame();

		static void Draw();
		static void OpenLayout(std::string_view layoutName);

		static void RegisterViewTypes();
		static void OpenView(std::string_view viewName, int id = -1);

		static EditorViewRegistry& GetViewRegistry();

		static void SaveNewLayout(std::string_view layoutName);

	private:
		static void Internal_OpenLayout();

	private:
		static inline EditorViewRegistry registry;
		static inline std::vector<EditorViewInstance*> activeViews;

		static inline std::string layoutNameToopen;








	public:


	};
}