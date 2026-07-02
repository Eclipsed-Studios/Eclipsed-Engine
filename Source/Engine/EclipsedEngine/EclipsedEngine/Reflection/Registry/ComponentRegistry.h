#pragma once

#include <functional>
#include <unordered_map>
#include <string>

#include "CoreEngine/Macros/defines.h"

namespace Eclipse
{
    class Component;

    using AddCompWithIdFunc = std::function<Component* (unsigned, unsigned)>;
    using AddCompFunc = std::function<Component* (unsigned)>;

    struct RegisteredComp
    {
        AddCompWithIdFunc addCompWithId;
        AddCompFunc addComp;

        std::string name;
        std::string rttiName;
    };

    class ComponentRegistry final
    {
    public:
        ComponentRegistry() = delete;
        ~ComponentRegistry() = delete;

    private:
        static ECLIPSED_API std::unordered_map<std::string, RegisteredComp> rttiNameToCompData;
        static ECLIPSED_API std::unordered_map<std::string, RegisteredComp> compNameToCompData;

    public:
        static ECLIPSED_API void RegisterComponent(
            const std::string& typeName,
            const std::string& rttiName,
            AddCompWithIdFunc addCompWithIdFunc,
            AddCompFunc addCompFunc,
            bool isGameComponent = false
        );

        static bool IsRegistered(const std::string& name);

        static void ClearRegisteredGameComponents();

        static ECLIPSED_API AddCompFunc GetAddComponentByTypeName(const std::string& typeName);
        static ECLIPSED_API AddCompFunc GetAddComponentByRttiTypeName(const std::string& rttiTypeName);

        static ECLIPSED_API AddCompWithIdFunc GetAddComponentWithIdByTypeName(const std::string& typeName);
        static ECLIPSED_API AddCompWithIdFunc GetAddComponentWithIdByRttiTypeName(const std::string& rttiTypeName);

        template<typename T>
        static AddCompFunc& GetAddComponent()
        {
            return GetAddComponentByRttiTypeName(typeid(T).name());
        }

        template<typename T>
        static AddCompWithIdFunc& GetAddComponentWithID()
        {
            return GetAddComponentWithIdByRttiTypeName(typeid(T).name());
        }

        static std::unordered_map<std::string, RegisteredComp>& GetComponentRttiMap();
        static std::unordered_map<std::string, RegisteredComp>& GetComponentTypeNameMap();

        static ECLIPSED_API inline std::vector<std::string> gameComponents;
    };
} // namespace Eclipse
