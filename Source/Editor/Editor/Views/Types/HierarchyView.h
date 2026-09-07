#pragma once

#include "Editor/Views/IEditorView.h"

#include <vector>
#include <set>
#include <filesystem>

#include <rapidjson/document.h>

namespace Eclipse
{
	class Canvas;
	class GameObject;
}

namespace Eclipse::Editor
{
	class HierarchyView : public EditorView<HierarchyView>
	{
		BASIC_VIEW("Hierarchy")

	public:
		void Draw() override;
	};
}	