#pragma once

#include <unordered_map>
#include <string>

namespace ENGINE_NAMESPACE::Editor
{
	class WindowRegistry 
	{
	public:
		template<typename T>
		static void RegisterWindow(const std::string& name);

		static void* GetWindow(const std::string& name);

		static const std::unordered_map<std::string, void*>& GetWindows();

	private:
		static inline std::unordered_map<std::string, void*> registeredWindows;
	};

	template<typename T>
	inline void WindowRegistry::RegisterWindow(const std::string& name)
	{
		registeredWindows[name] = (void*) new T();
	}
}