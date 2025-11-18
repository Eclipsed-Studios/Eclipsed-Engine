#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <stdexcept>

#ifdef ECLIPSE_UTILITIES_EXPORTS
#define UTILITIES_API __declspec(dllexport)
#else
#define UTILITIES_API __declspec(dllimport)
#endif

namespace Eclipse::Utilities
{
    class UTILITIES_API MainSingleton
    {
    public:
        template<typename T>
        static T& GetInstance();

        template<typename T>
        static T& RegisterInstance();

        template<typename T>
        static bool Exists();

    private:
        static inline std::unordered_map<std::type_index, std::shared_ptr<void>> mySingletons;
    };

    template<typename T>
    inline T& MainSingleton::GetInstance()
    {
        auto it = mySingletons.find(typeid(T));
        if (it != mySingletons.end())
            return *std::static_pointer_cast<T>(it->second);
        throw std::runtime_error("Singleton not registered.");
    }

    template<typename T>
    inline T& MainSingleton::RegisterInstance()
    {
        auto instance = std::make_shared<T>();
        mySingletons[typeid(T)] = instance;
        return *instance;
    }

    template<typename T>
    inline bool MainSingleton::Exists()
    {
        return mySingletons.find(typeid(T)) != mySingletons.end();
    }
}
