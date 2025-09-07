#pragma once

#include "Window.h"

#include <filesystem>

#include <rapidjson/rapidjson/document.h>

namespace ENGINE_NAMESPACE::Editor
{
	class InputEditorWindow final : public AbstractWindow
	{
	public:
		InputEditorWindow(const int& aId = -1);

		void Open() override;
		void Update() override;
		void Close() override;

	public:
		bool isButtonEditing;
	};
}