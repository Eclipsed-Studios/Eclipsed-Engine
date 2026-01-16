#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include "CoreEngine/Math/Vector/Vector2.h"
#include <stdexcept>
#include "rapidjson/document.h"

#define SETTING_TYPE(_TYPE) _TYPE, std::vector<_TYPE>

namespace Eclipse::Settings
{
	using SettingValue = std::variant<
		SETTING_TYPE(bool), 
		SETTING_TYPE(int),
		SETTING_TYPE(unsigned int),
		SETTING_TYPE(double),
		SETTING_TYPE(float),
		SETTING_TYPE(std::string),
		SETTING_TYPE(Math::Vector2f),
		SETTING_TYPE(Math::Vector2i)>;

	struct SettingsLayer { std::unordered_map<std::string, SettingValue> values; };

	class SettingsRegistry
	{
	public:
		SettingsRegistry() = delete;
		~SettingsRegistry() = delete;

	public:
		static void SaveDefaults(const char* layerName);
		static void SaveDefaults();

		static void SaveGraphicsDefaults();
		static void SaveEngineDefaults();
		static void SaveEditorDefaults();
		static void SaveUserDefaults();
		static void SaveBuildDefaults();
		static void SaveNetworkDefaults();
		static void SavePhysicsDefaults();

		static void Save();
		static void Load();

	public:
		static void PushOverride(const char* settingsKey, SettingValue value);

		template<typename T>
		static T& Get(const char* settingsKey);

		template<typename T>
		static T* TryGet(const char* settingsKey);

		template<typename T>
		static SettingValue& Set(const char* settingKey, T value);
		static SettingValue& Set(const char* settingKey);

		template<typename T>
		static void AddToList(const char* settingKey, T value);

	private:
		static void Clear();
		static void LoadLayer(const char* layerName);
		static void SaveLayer(const char* layerName);

	private:
		static rapidjson::Value VariantToJson(const SettingValue& SettingValue, rapidjson::Document::AllocatorType& allocator);
		static SettingValue JsonToVariant(const rapidjson::Value& jsonValue);

	private:
		static SettingValue& GetValue(const char* settingsKey);
		static SettingValue& AddValue(SettingsLayer& layer, const char* key);

	private:
		static std::unordered_map<std::string, SettingsLayer> layers;
	};

	template<typename T>
	inline T& SettingsRegistry::Get(const char* settingsKey)
	{
		SettingValue& storedValue = GetValue(settingsKey);
		if (T* value = std::get_if<T>(&storedValue))
			return *value;

		throw std::runtime_error("SettingsRegistry wrong type.");
	}

	template<typename T>
	inline T* SettingsRegistry::TryGet(const char* settingsKey)
	{
		return std::get_if<T>(&GetValue(settingsKey));
	}
	template<typename T>
	inline SettingValue& SettingsRegistry::Set(const char* settingKey, T value)
	{
		SettingValue& stored = Set(settingKey);

		return stored;
	}

	template<typename T>
	inline void SettingsRegistry::AddToList(const char* settingKey, T value)
	{
		SettingValue& setting = GetValue(settingKey);

		if (!std::holds_alternative<std::vector<std::decay_t<T>>>(setting))
		{
			setting = std::vector<std::decay_t<T>>{};
		}

		std::get<std::vector<std::decay_t<T>>>(setting)
			.push_back(std::forward<T>(value));
	}
}