#include "WindowRegistry.h"

void* ENGINE_NAMESPACE::Editor::WindowRegistry::GetWindow(const std::string& name)
{
    return registeredWindows[name];
}

const std::unordered_map<std::string, void*>& ENGINE_NAMESPACE::Editor::WindowRegistry::GetWindows()
{
    return WindowRegistry::registeredWindows;
}
