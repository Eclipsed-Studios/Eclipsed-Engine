#include "MainSingleton.h"

namespace Eclipse
{
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
        auto instance = new T();
        mySingletons[typeid(T)] = instance;
        return *instance;
    }

    template<typename T>
    inline bool MainSingleton::Exists()
    {
        return mySingletons.find(typeid(T)) != mySingletons.end();
    }
}