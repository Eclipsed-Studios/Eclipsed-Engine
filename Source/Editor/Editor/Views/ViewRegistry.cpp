#include "ViewRegistry.h"

#include "Editor/Views/AbstractView.h"

namespace Eclipse::Editor
{
	CreateNewViewFunc ViewRegistry::GetView(const std::string& name)
	{
		return registeredViews[name];
	}

	const std::unordered_map<std::string, CreateNewViewFunc>& ViewRegistry::GetViews()
	{
		return ViewRegistry::registeredViews;
	}

	void ViewRegistry::RegisterView(const std::string& name, CreateNewViewFunc func)
	{
		registeredViews[name] = func;
	}
}