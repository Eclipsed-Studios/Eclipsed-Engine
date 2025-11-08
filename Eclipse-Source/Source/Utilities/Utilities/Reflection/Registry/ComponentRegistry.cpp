#include "ComponentRegistry.h"
#include <Windows.h>
#include <iostream>

#ifdef ECLIPSED_EDITOR
namespace Eclipse
{
    // Define static member variables (they live only in the DLL)
    std::unordered_map<std::string, std::function<Component* (unsigned, unsigned)>> ComponentRegistry::addComponentMap;
    std::unordered_map<std::string, std::function<Component* (unsigned)>> ComponentRegistry::inspectorAddComponentMap;

    bool ComponentRegistry::IsDLLCall()
    {
        HMODULE hModule = nullptr;
        GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
            reinterpret_cast<LPCTSTR>(IsDLLCall),
            &hModule);

        static HMODULE engineModule = GetModuleHandle(nullptr);
        return hModule != engineModule;
    }

    void ComponentRegistry::Register(const std::string& typeName,
        std::function<Component* (unsigned, unsigned)> addComponentMethod)
    {
        auto& map = GetAddComponentMap();
        map[typeName] = addComponentMethod;
    }

    std::function<Component* (unsigned, unsigned)> ComponentRegistry::GetAddComponent(const std::string& typeName)
    {
        auto& map = GetAddComponentMap();
        auto it = map.find(typeName);
        if (it != map.end())
        {
            return it->second;
        }
        return [](unsigned, unsigned) { return nullptr; };
    }

    std::unordered_map<std::string, std::function<Component* (unsigned, unsigned)>>&
        ComponentRegistry::GetAddComponentMap()
    {
        return addComponentMap;
    }

    void ComponentRegistry::RegisterInspector(const std::string& typeName,
        std::function<Component* (unsigned)> addComponentMethod)
    {
        auto& map = GetInspectorAddComponentMap();
        std::cout << "RegisterInspector - Map address: " << &map
            << ", Size: " << map.size()
            << ", Adding: " << typeName
            << ", From: " << (IsDLLCall() ? "DLL" : "ENGINE") << std::endl;
        map[typeName] = addComponentMethod;
    }

    std::function<Component* (unsigned)> ComponentRegistry::GetInspectorAddComponent(const std::string& typeName)
    {
        auto& map = GetInspectorAddComponentMap();
        auto it = map.find(typeName);
        if (it != map.end())
        {
            return it->second;
        }
        return [](unsigned) { return nullptr; };
    }

    std::unordered_map<std::string, std::function<Component* (unsigned)>>&
        ComponentRegistry::GetInspectorAddComponentMap()
    {
        return inspectorAddComponentMap;
    }
} // namespace Eclipse
#endif