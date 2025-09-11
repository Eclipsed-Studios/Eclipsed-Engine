#pragma once

#include "WindowBase.h"

namespace Eclipse::Editor
{
	class ConsoleWindow final : public AbstractWindow 
	{
		BASE_SELECTION(ConsoleWindow, "Console")

	public:
		void Update() override;

	private:
		bool myShouldCollapseMessages = false;
		bool myShouldShowMessages = true;
		bool myShouldShowWarnings = true;
		bool myShouldShowErrors = true;
	};
}