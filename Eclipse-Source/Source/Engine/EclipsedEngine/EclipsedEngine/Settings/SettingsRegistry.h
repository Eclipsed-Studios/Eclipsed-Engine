#pragma once

#include <variant>
#include <string>
#include <unordered_map>
#include "CoreEngine/Math/Vector/Vector2.h"
#include <stdexcept>
#include "rapidjson/document.h"

// Layers
/*
	Graphics
	Engine
	Editor
	User
	Build
	Network
	Physics
*/

namespace Eclipse::Settings
{
	using SettingValue = std::variant<bool, int, double, float, std::string, Math::Vector2i, Math::Vector2f>; // Needs to be updated depending on the types added.
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

	private:
		static void Clear();
		static void LoadLayer(const char* layerName);
		static void SaveLayer(const char* layerName);

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
}