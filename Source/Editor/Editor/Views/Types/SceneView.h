#pragma once

#include "Editor/Views/IEditorView.h"

namespace Eclipse::Editor
{
	class SceneView : public EditorView<SceneView>
	{
		BASIC_VIEW("Scene")

	public:
		void Draw() override {}
	};
}