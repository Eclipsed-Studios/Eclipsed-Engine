#pragma once

#include "Editor/Views/IEditorView.h"

namespace Eclipse::Editor
{
	class InspectorView : public EditorView<InspectorView>
	{
		BASIC_VIEW("Inspector")

	public:
		void Draw() override {}
	};
}