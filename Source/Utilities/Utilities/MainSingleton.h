#pragma once

#include <unordered_map>
#include <typeinfo>
#include <assert.h>
#include <string>
#include <stdexcept>

namespace Zultools
{
	class MainSingleton
	{
	public:
		static void Init();


		template<typename T>
		static T& GetInstance();

		static const bool& IsSetup();

		template <typename T>
		static T& RegisterInstance();

		template <typename T>
		static bool Exists();

	private:
		static std::unordered_map<std::string, void*> mySingletons;
		static bool myIsInitialized;
	};

	template<typename T>
	inline T& MainSingleton::GetInstance()
	{
		auto it = mySingletons.find(typeid(T).name());
		if (it != mySingletons.end()) {
			return *(static_cast<T*>(it->second));
		}

		assert("Singleton not registered.");
		throw std::runtime_error("Singleton not registered.");
	}

	template<typename T>
	inline T& MainSingleton::RegisterInstance()
	{
		mySingletons[typeid(T).name()] = static_cast<void*>(new T);
		return *(static_cast<T*>(mySingletons[typeid(T).name()]));
	}

	template<typename T>
	inline bool MainSingleton::Exists()
	{
		auto it = mySingletons.find(typeid(T).name());
		if (it != mySingletons.end()) {
			return true;
		}

		return false;
	}
}
