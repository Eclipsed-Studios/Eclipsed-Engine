#include "Window.h"

ENGINE_NAMESPACE::Editor::AbstractWindow::AbstractWindow(const std::string& name, const int& aId)
	: instanceID(aId == -1 ? Random::GetValue<int>() : aId), windowName(name)
{
}
