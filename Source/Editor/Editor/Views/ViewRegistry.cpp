#include "ViewRegistry.h"

#include "Editor/Views/AbstractView.h"

namespace Eclipse::Editor
{
	AbstractView* ViewRegistry::GetView(const std::string& name)
	{
		return registeredViews[name];
	}

	const std::unordered_map<std::string, AbstractView*>& ViewRegistry::GetViews()
	{
		return ViewRegistry::registeredViews;
	}
}