#pragma once

#include "Window.h"

namespace ENGINE_NAMESPACE::Editor
{
	class ConsoleWindow final : public AbstractWindow {
		BASE_WINDOW(ConsoleWindow, "Console")

	public:
		void Update() override;

	private:
		bool myShouldCollapseMessages = false;
		bool myShouldShowMessages = true;
		bool myShouldShowWarnings = true;
		bool myShouldShowErrors = true;
	};
}