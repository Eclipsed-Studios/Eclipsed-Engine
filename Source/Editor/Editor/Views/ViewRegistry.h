#pragma once

#include <unordered_map>
#include <string>


namespace Eclipse::Editor
{
	class AbstractView;
	class ViewRegistry
	{
	public:
		template<typename T>
		static void RegisterView(const std::string& name);

		static AbstractView* GetView(const std::string& name);

		static const std::unordered_map<std::string, AbstractView*>& GetViews();

	private:
		static inline std::unordered_map<std::string, AbstractView*> registeredViews;
	};

	template<typename T>
	inline void ViewRegistry::RegisterView(const std::string& name)
	{
		registeredViews[name] = new T();
	}
}