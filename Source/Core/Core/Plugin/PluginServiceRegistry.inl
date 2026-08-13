#include "PluginServiceRegistry.hpp"

namespace Eclipse::Core
{
	template<typename T>
	void PluginServiceRegistry::Register(T* service)
	{
		services[typeid(T)] = service;
	}

	template<typename T>
	T* PluginServiceRegistry::Get()
	{
		auto it = services.find(typeid(T));

		if (it == services.end())
			return nullptr;

		return static_cast<T*>(it->second);
	}
}