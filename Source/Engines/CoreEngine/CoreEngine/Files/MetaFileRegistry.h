#pragma once

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson/filewritestream.h"

#include <string>

namespace Eclipse
{
	/// <summary>
	/// Only used by the editor. The complete game will have this data stored in its asset bundle.
	/// </summary>
	class MetaFileRegistry final
	{
	public:
		static void Load();
		static void Save();

		template<typename T>
		static T Get(const char* aPath, const char* aName);

		template<typename T>
		static void Set(const char* aPath, const char* aName, const T& aValue);

	private:
		static inline rapidjson::Document myDocument;
	};

	template<typename T>
	inline T MetaFileRegistry::Get(const char* aPath, const char* aName)
	{
		using namespace rapidjson;

		if (!myDocument.HasMember(aPath)) return T();
		const Value& fileData = myDocument[aPath];

		if (!fileData.HasMember(aName)) return T();
		const Value& data = fileData[aName];

		if constexpr (std::is_same<T, int>::value) return data.GetInt();
		else if constexpr (std::is_same<T, bool>::value) return data.GetBool();

		return T();
	}

	template<typename T>
	inline void MetaFileRegistry::Set(const char* aPath, const char* aName, const T& aValue)
	{
        using namespace rapidjson;

        Document::AllocatorType& allocator = myDocument.GetAllocator();

        if (!myDocument.IsObject())
        {
            myDocument.SetObject();
        }

        Value* fileData = nullptr;
        if (myDocument.HasMember(aPath))
        {
            Value& existing = myDocument[aPath];
            if (!existing.IsObject())
            {
                existing.SetObject();
            }
            fileData = &existing;
        }
        else
        {
            Value newObj(kObjectType);
            myDocument.AddMember(Value(aPath, allocator).Move(), newObj, allocator);
            fileData = &myDocument[aPath];
        }

        Value key(aName, allocator);
        Value val;
        if constexpr (std::is_arithmetic_v<T>::value) 
        {
            val = Value(aValue);
        }
        else if constexpr (std::is_same_v<T, std::string>::value || std::is_same_v<T, const char*>::value)
        {
            val = Value(aValue, allocator);
        }

        if (fileData->HasMember(aName))
        {
            (*fileData)[aName] = val;
        }
        else
        {
            fileData->AddMember(key.Move(), val.Move(), allocator);
        }
	}
}