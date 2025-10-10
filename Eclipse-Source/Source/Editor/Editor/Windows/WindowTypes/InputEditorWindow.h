#pragma once

#include "Editor/Windows/WindowBase.h"


namespace Eclipse::Editor
{
	class InputEditorWindow final : public AbstractWindow
	{
		BASE_SELECTION(InputEditorWindow, "Input Editor", "Settings");

	public:
		void Update() override;

	public:
		bool isButtonEditing = false;
	};
}