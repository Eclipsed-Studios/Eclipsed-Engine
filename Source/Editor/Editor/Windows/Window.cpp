#include "Window.h"

namespace ENGINE_NAMESPACE::Editor
{
	const int& AbstractWindow::GetID() { return myID; }
	const int& AbstractWindow::GetID() const { return myID; }

	const std::string& AbstractWindow::GetWindowName() { return myWindowName; }
	const std::string& AbstractWindow::GetWindowName() const { return myWindowName; }
}