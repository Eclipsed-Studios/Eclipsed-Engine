#pragma once

#include "Interfaces/Serializable.h"

#include <unordered_map>
#include <string>
#include <typeindex>
#include <any>
#include <type_traits>
#include "Math/Vector/Vector2.h"

namespace ENGINE_NAMESPACE::Utilities
{
	class BlackBoard : public ISerializable
	{
	public:
		BlackBoard() = default;
		~BlackBoard() = default;

	public:
		template<typename T>
		T Get(const std::string& name);

		template<typename T>
		void Add(const std::string& name, const T& value);

	public:
		rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		void Load(const rapidjson::Value& aValue) override;

	private:
		template<typename T>
		void LoadArray(const rapidjson::Value& aValue);

	private:
		using ValueList = std::unordered_map<std::string, std::any>;
		std::unordered_map<std::type_index, ValueList> myData;
	};

	template<typename T>
	inline T BlackBoard::Get(const std::string& name)
	{
		//const auto idx = std::type_index(typeid(T));

		//auto typeIt = myData.find(idx);
		//if (typeIt == myData.end()) 
		//{
		//	throw std::runtime_error("type not found");
		//}

		//const auto& list = typeIt->second;
		//auto nameIt = list.find(name);
		//if (nameIt == list.end()) 
		//{
		//	throw std::runtime_error("name not found");
		//}

		//return std::any_cast<T>(nameIt->second);
	}
	
	template<typename T>
	inline void BlackBoard::Add(const std::string& name, const T& value)
	{
		myData[typeid(T)][name] = value;
	}

	template<typename T>
	inline void BlackBoard::LoadArray(const rapidjson::Value& aValue)
	{
		auto f = typeid(T).name();
		if (aValue.HasMember(f))
		{
			const char* typeKey = typeid(T).name();
			const rapidjson::Value& objList = aValue[typeKey];
			auto& list = myData[std::type_index(typeid(T))];

			for (const auto& entry : objList.GetArray())
			{
				if (!entry.IsObject())
					continue;

				int i =  entry.MemberCount();

				for (auto m = entry.MemberBegin(); m != entry.MemberEnd(); ++m)
				{
					const std::string name = m->name.GetString();
					const rapidjson::Value& v = m->value;

					if (v.IsInt())
					{
						list[name] = v.GetInt();
					}
					else if (v.IsString())
					{
						list[name] = v.GetString();
					}
					else if (v.IsFloat())
					{
						list[name] = v.GetFloat();
					}
					else if  (v.IsObject() && v.HasMember("x") && v.HasMember("y"))
					{
						Math::Vector2i vec;
						vec.Load(v);
						list[name] = vec;
					}
				}
			}
		}
	}
}