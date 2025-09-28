#pragma once

#include "WindowBase.h"
#include <DebugLogger.h>

namespace Eclipse::Editor
{
	class ConsoleWindow final : public AbstractWindow 
	{
		BASE_SELECTION(ConsoleWindow, "Console")

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