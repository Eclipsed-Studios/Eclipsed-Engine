#pragma once
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui.h"

#include <string>
#include "IEditorView.h"

namespace Eclipse::Editor
{
	struct EditorViewInstance
	{
		~EditorViewInstance()  
		{
			delete view;
		}

		std::string idString;
		int id;
		bool open = true;
		IEditorView* view;
	};
}