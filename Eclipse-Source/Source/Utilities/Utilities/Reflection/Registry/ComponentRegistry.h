#pragma once
#include <functional>
#include <unordered_map>
#include <string>

namespace Eclipse
{
#ifdef ECLIPSED_EDITOR
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

    class Component;

    class ComponentRegistry final
    {
    public:
        ComponentRegistry() = delete;
        ~ComponentRegistry() = delete;

    private:
        using AddComponentMap = std::unordered_map<std::string, std::function<Component* (unsigned, unsigned)>>;
        using InspectorAddComponentMap = std::unordered_map<std::string, std::function<Component* (unsigned)>>;

        static ENGINE_API AddComponentMap addComponentMap;
        static ENGINE_API  InspectorAddComponentMap inspectorAddComponentMap;

    public:
        static bool IsRegisteredInspector(const std::string& typeName);
        static bool IsRegisteredScene(const std::string& typeName);


        static void ClearRegisteredGameComponents();

        static void Register(const std::string& typeName, std::function<Component* (unsigned, unsigned)> addComponentMethod, bool isGame = false);
        static std::function<Component* (unsigned, unsigned)> GetAddComponent(const std::string& typeName);
        static std::unordered_map<std::string, std::function<Component* (unsigned, unsigned)>>& GetAddComponentMap();

        static void RegisterInspector(const std::string& typeName, std::function<Component* (unsigned)> addComponentMethod, bool isGame = false);
        static std::function<Component* (unsigned)> GetInspectorAddComponent(const std::string& typeName);
        static std::unordered_map<std::string, std::function<Component* (unsigned)>>& GetInspectorAddComponentMap();

        static inline std::vector<std::string> gameComponents;
    };
} // namespace Eclipse
