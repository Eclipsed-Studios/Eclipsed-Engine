#pragma once

#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <assert.h>
#include <string>
#include <stdexcept>

namespace ENGINE_NAMESPACE::Utilities
{
	class MainSingleton
	{
	public:
		static void Init();


		template<typename T>
		static T& GetInstance();

		template<typename T>
		static T* GetInstancePtr();

		static const bool& IsSetup();

		template <typename T>
		static T& RegisterInstance();

		template <typename T>
		static bool Exists();

	private:
		static std::unordered_map<std::type_index, void*> mySingletons;
		static bool myIsInitialized;
	};

	template<typename T>
	inline T& MainSingleton::GetInstance()
	{
		auto it = mySingletons.find(typeid(T));
		if (it != mySingletons.end()) {
			return *(static_cast<T*>(it->second));
		}

		assert("Singleton not registered.");
		throw std::runtime_error("Singleton not registered.");
	}

	template<typename T>
	inline T* MainSingleton::GetInstancePtr()
	{
		auto it = mySingletons.find(typeid(T));
		if (it != mySingletons.end()) {
			return (T*)it->second;
		}

		assert("Singleton not registered.");
		throw std::runtime_error("Singleton not registered.");
	}

	template<typename T>
	inline T& MainSingleton::RegisterInstance()
	{
		mySingletons[typeid(T)] = static_cast<void*>(new T);
		return *(static_cast<T*>(mySingletons[typeid(T)]));
	}

	template<typename T>
	inline bool MainSingleton::Exists()
	{
		auto it = mySingletons.find(typeid(T));
		if (it != mySingletons.end()) {
			return true;
		}

		return false;
	}
}
