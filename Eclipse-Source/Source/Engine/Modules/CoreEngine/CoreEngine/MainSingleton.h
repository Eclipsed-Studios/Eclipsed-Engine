#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <stdexcept>

namespace Eclipse
{
    class MainSingleton
    {
    public:
        template<typename T>
        static T& GetInstance();

        template<typename T>
        static T& RegisterInstance();

        template<typename T>
        static bool Exists();

    private:
        static inline std::unordered_map<std::type_index, void*> mySingletons;
    };
}

#include "MainSingleton.inl"