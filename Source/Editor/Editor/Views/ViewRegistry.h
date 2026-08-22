#pragma once

#include <unordered_map>
#include <string>


namespace Eclipse::Editor
{
	using CreateNewViewFunc = void*(*)();

	class AbstractView;
	class ViewRegistry
	{
	public:
		static void RegisterView(const std::string& name, CreateNewViewFunc func);

		static CreateNewViewFunc GetView(const std::string& name);

		static const std::unordered_map<std::string, CreateNewViewFunc>& GetViews();

	private:
		static inline std::unordered_map<std::string, CreateNewViewFunc> registeredViews;
	};
}