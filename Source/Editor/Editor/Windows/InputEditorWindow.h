#pragma once

#include "Window.h"

#include <filesystem>

#include <rapidjson/rapidjson/document.h>

namespace ENGINE_NAMESPACE::Editor
{
	class InputEditorWindow final : public AbstractWindow
	{
		BASE_WINDOW(InputEditorWindow, "Input Editor");

	public:
		void Update() override;

	public:
		bool isButtonEditing;
	};
}