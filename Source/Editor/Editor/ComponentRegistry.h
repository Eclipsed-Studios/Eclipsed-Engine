#pragma once

#include <unordered_map>
#include <string>
#include <functional>

//#include "ECS/ComponentManager.h"


namespace ENGINE_NAMESPACE::Editor
{
	class ComponentRegistry 
	{
	public:
		static void RegisterComponent(const std::string& name, std::function<void(int)> addComponentMethod);

		static void AddComponent(const std::string& name, int id);

		static const std::unordered_map<std::string, std::function<void(int)>>& GetComponents();

	private:
		static inline std::unordered_map<std::string, std::function<void(int)>> components;
	};
}