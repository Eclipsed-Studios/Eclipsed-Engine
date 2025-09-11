#pragma once

#include <unordered_map>
#include <string>
#include <functional>

//#include "ECS/ComponentManager.h"


namespace Eclipse::Editor
{
	class ComponentRegistry 
	{
    public:
        static void RegisterComponent(const std::string& name, std::function<void(int)> addComponentMethod) 
        {
            GetMap()[name] = addComponentMethod;
        }

        static void AddComponent(const std::string& name, int id) 
        {
            auto& map = GetMap();
            auto it = map.find(name);
            if (it != map.end()) 
            {
                it->second(id);
            }
        }

        static const std::unordered_map<std::string, std::function<void(int)>>& GetComponents() 
        {
            return GetMap();
        }

    private:
        static std::unordered_map<std::string, std::function<void(int)>>& GetMap() 
        {
            static std::unordered_map<std::string, std::function<void(int)>> map;
            return map;
        }
	};
}