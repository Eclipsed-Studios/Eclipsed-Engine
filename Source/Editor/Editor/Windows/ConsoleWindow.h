#pragma once

#include "Window.h"

class ConsoleWindow final : public AbstractWindow {

public:
	ConsoleWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

private:
	bool myShouldCollapseMessages = false;
	bool myShouldShowMessages = true;
	bool myShouldShowWarnings = true;
	bool myShouldShowErrors = true;
};