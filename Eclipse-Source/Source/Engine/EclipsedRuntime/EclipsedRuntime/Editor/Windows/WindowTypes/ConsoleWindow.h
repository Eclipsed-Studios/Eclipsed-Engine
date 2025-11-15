#pragma once

#include "EclipsedRuntime/Editor/Windows/WindowBase.h"


namespace Eclipse
{
	struct Message;
}

namespace Eclipse::Editor
{
	class ConsoleWindow final : public AbstractWindow 
	{
		EDITOR_WINDOW_BASE_2(ConsoleWindow, "Console")

	public:
		void Update() override;

	private:
		void DisplayMessage(const Message& aMessage);

	private:
		bool myAlwaysAtBottom = false;
		bool myShouldCollapseMessages = false;
		bool myShouldShowMessages = true;
		bool myShouldShowWarnings = true;
		bool myShouldShowErrors = true;
	};
}