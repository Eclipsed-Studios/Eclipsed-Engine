#pragma once

#include "EclipsedEngine/Editor/Windows/WindowBase.h"
#include "Core/Logger/DebugLogger.h"

namespace Eclipse { struct DebugMessage; }

namespace Eclipse::Editor
{
	class ConsoleWindow final : public AbstractWindow
	{
		EDITOR_WINDOW_BASE_2(ConsoleWindow, "Console")

	public:
		void Update() override;

	private:
		void DisplayMessage(const DebugMessage& aMessage);

	private:
		bool myAlwaysAtBottom = false;
		bool myShouldCollapseMessages = false;
		bool myShouldShowMessages = true;
		bool myShouldShowWarnings = true;
		bool myShouldShowErrors = true;

		ImGuiTextFilter msgFilter{};
		ImGuiTextFilter fileFilter{};
	};
}