#pragma once

#include <functional>
#include <unordered_map>
#include <string>



namespace Eclipse
{
	class Component;
	class ComponentRegistry final
	{
	public:
		ComponentRegistry() = delete;
		~ComponentRegistry() = delete;

	public:
		static void Register(const std::string& aTypeName, std::function<Component* (unsigned, unsigned)> aAddComponentMethod)
		{
			auto& map = GetAddComponentMap();
			map[aTypeName] = aAddComponentMethod;
		}

		static std::function<Component* (unsigned, unsigned)> GetAddComponent(const std::string& aTypeName)
		{
			auto& map = GetAddComponentMap();
			auto it = map.find(aTypeName);
			if (it != map.end())
			{
				return it->second;
			}

			return [](unsigned, unsigned) {return nullptr;};
		}

		static std::unordered_map<std::string, std::function<Component* (unsigned, unsigned)>>& GetAddComponentMap()
		{
			static std::unordered_map<std::string, std::function<Component* (unsigned, unsigned)>> map;
			return map;
		}



		static void RegisterInspector(const std::string& aTypeName, std::function<Component* (unsigned)> aAddComponentMethod)
		{
			auto& map = GetInspectorAddComponentMap();
			map[aTypeName] = aAddComponentMethod;
		}

		static std::function<Component* (unsigned)> GetInspectorAddComponent(const std::string& aTypeName)
		{
			auto& map = GetInspectorAddComponentMap();
			auto it = map.find(aTypeName);
			if (it != map.end())
			{
				return it->second;
			}

			return [](unsigned) {return nullptr;};
		}

		static std::unordered_map<std::string, std::function<Component* (unsigned)>>& GetInspectorAddComponentMap()
		{
			static std::unordered_map<std::string, std::function<Component* (unsigned)>> map;
			return map;
		}
	};
}