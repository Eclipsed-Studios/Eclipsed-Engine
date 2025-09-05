#pragma once

#include "Interfaces/Serializable.h"

#include <unordered_map>
#include <string>
#include <typeindex>
#include <functional>
#include <any>
#include <type_traits>
#include "Math/Vector/Vector2.h" 

namespace ENGINE_NAMESPACE::Utilities
{
	struct BlackBoardValue
	{
		std::type_index type = typeid(void);
		std::any value;
	};

	class BlackBoard : public ISerializable
	{
	public:
		BlackBoard() = default;
		~BlackBoard() = default;

	public:
		rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		void Load(const rapidjson::Value& aValue) override;

	public:
		template<typename T>
		void Set(const char* name, const T& value);

		template<typename T>
		const T& Add(const char* name, const T& value);

		template<typename T>
		const T& Get(const char* name);

	private:
		using BlackBoardList =  std::unordered_map<std::string, BlackBoardValue>;
		std::unordered_map<std::type_index, BlackBoardList> myData;


		using Serializer = std::function<rapidjson::Value(const std::any&, rapidjson::Document::AllocatorType&)>;
		std::unordered_map<std::type_index, Serializer> mySerializers;

		rapidjson::Document myJsonDocument;


	private:
		template<typename T>
		void RegisterSerializer();
	};

	template<typename T>
	inline void BlackBoard::Set(const char* name, const T& value)
	{
		const std::type_index& idx = typeid(T);
		BlackBoardList& list = myData[idx];

		BlackBoardValue& val = list[name];
		val.value = value;
	}

	template<typename T>
	inline const T& BlackBoard::Add(const char* name, const T& value)
	{
		const std::type_index& idx = typeid(T);
		BlackBoardList& list = myData[idx];

		BlackBoardValue bbValue;
		bbValue.type = idx;
		bbValue.value = value;

		BlackBoardValue& val = list[name];
		val = bbValue;

		RegisterSerializer<T>();

		return std::any_cast<T&>(val.value);
	}

	template<typename T>
	inline const T& BlackBoard::Get(const char* name)
	{
		const std::type_index& idx = typeid(T);
		BlackBoardList& list = myData[idx];

		const BlackBoardValue& val = list[name];

		return std::any_cast<const T&>(val.value);
	}

	template<typename T>
	inline void BlackBoard::RegisterSerializer()
	{
		if constexpr (std::is_base_of_v<ISerializable, T>)
		{
			mySerializers[typeid(T)] = [](const std::any& a, auto& alloc) {
				return std::any_cast<const T&>(a).Save(alloc);
				};
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			mySerializers[typeid(T)] = [](const std::any& a, auto& alloc) {
				const auto& s = std::any_cast<const std::string&>(a);
				return rapidjson::Value(s.c_str(), alloc);
				};
		}
		else if constexpr (std::is_arithmetic_v<T>)
		{
			mySerializers[typeid(T)] = [](const std::any& a, auto& alloc) {
				if constexpr (std::is_integral_v<T>)
					return rapidjson::Value(std::any_cast<T>(a));
				else
					return rapidjson::Value(static_cast<double>(std::any_cast<T>(a)));
				};
		}
		else
		{
			mySerializers[typeid(T)] = [](const std::any& a, auto& alloc) {
				return rapidjson::Value(std::any_cast<T>(a));
				};
		}
	}
}