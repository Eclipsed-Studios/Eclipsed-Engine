#pragma once

#include <typeindex>
#include<unordered_map>

namespace Eclipse::Core
{
	class PluginServiceRegistry final
	{
	public:
		template<typename T>
		void Register(T* service);

		template<typename T>
		T* Get();

	private:
		std::unordered_map<std::type_index, void*> services;
	};
}