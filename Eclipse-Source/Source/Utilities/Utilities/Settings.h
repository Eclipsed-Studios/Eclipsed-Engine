#pragma once

#include "rapidjson/rapidjson/document.h"

namespace Eclipse
{
	class Settings
	{
	public:
		Settings(const char* aPath);
		~Settings();

	protected:
		template<typename T>
		T Get(const char* aSettingName);

		rapidjson::Value& Get(const char* aSettingName);

		template<typename T>
		void Set(const char* aSettingName, const T& aValue);

	private:
		rapidjson::Document myJsonDoc;
		std::string mySettingsPath;
	};


	template<typename T>
	inline void Settings::Set(const char* aSettingName, const T& aValue)
	{
		rapidjson::Document::AllocatorType& alloc = myJsonDoc.GetAllocator();

		rapidjson::Value key(aSettingName, alloc);

		rapidjson::Value val;

		if constexpr (Is_Std_String<T>::value)
		{
			val.SetString(aValue.c_str(), aValue.length(), alloc);
		}
		else if constexpr (Is_C_String<T>::value)
		{
			val.SetString(aValue, alloc);
		}
		else
		{
			val.Set(aValue, alloc);
		}


		if (!myJsonDoc.HasMember(aSettingName))
		{
			myJsonDoc.AddMember(rapidjson::Value(aSettingName, alloc), rapidjson::Value().Move(), alloc);
		}

		auto itr = myJsonDoc.FindMember(aSettingName);
		if (itr != myJsonDoc.MemberEnd())
		{
			itr->value = val;
		}
		else {
			myJsonDoc.AddMember(std::move(key), std::move(val), alloc);
		}
	}

	template<typename T>
	inline T Settings::Get(const char* aSettingName)
	{
	}
}