#pragma once

#include "WindowBase.h"

namespace Eclipse::Editor
{
	class InputEditorWindow final : public AbstractWindow
	{
		BASE_SELECTION(InputEditorWindow, "Input Editor", "GRiann");

	public:
		void Update() override;

	public:
		bool isButtonEditing = false;
	};
}