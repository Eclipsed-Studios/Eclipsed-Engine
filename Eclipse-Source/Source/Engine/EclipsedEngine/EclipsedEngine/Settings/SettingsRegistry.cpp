#include "SettingsRegistry.h"

#include "assert.h"

#include <filesystem>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "DefaultSettings.h"

#include "CoreEngine/PathManager.h"

using namespace rapidjson;

namespace Eclipse::Settings
{
	std::unordered_map<std::string, SettingsLayer> SettingsRegistry::layers;

#pragma region ---- SAVING

#pragma region ------ DEFAULTS

	void SettingsRegistry::SaveDefaults(const char* layerName)
	{
		if (!strcmp(layerName, "graphics"))		SaveGraphicsDefaults();
		else if (!strcmp(layerName, "engine"))	SaveEngineDefaults();
		else if (!strcmp(layerName, "editor"))	SaveEditorDefaults();
		else if (!strcmp(layerName, "user"))	SaveUserDefaults();
		else if (!strcmp(layerName, "build"))	SaveBuildDefaults();
		else if (!strcmp(layerName, "network"))	SaveNetworkDefaults();
		else if (!strcmp(layerName, "physics"))	SavePhysicsDefaults();
	}

	void SettingsRegistry::SaveDefaults()
	{
		SaveGraphicsDefaults();
		SaveBuildDefaults();
		SaveEditorDefaults();
		SaveEngineDefaults();
		SaveUserDefaults();
		SaveNetworkDefaults();
		SavePhysicsDefaults();
	}

	void SettingsRegistry::SaveGraphicsDefaults()
	{
		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		{ // DATA
			d.AddMember("fullscreen", Default::Graphics::Fullscreen, allocator);

			{
				Value resolution(kObjectType);
				resolution.AddMember("x", Default::Graphics::Resolution.x, allocator);
				resolution.AddMember("y", Default::Graphics::Resolution.y, allocator);

				d.AddMember("resolution", resolution.Move(), allocator);
			}
		}

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / "graphics");
		ofs << buffer.GetString();
		ofs.close();
	}

	void SettingsRegistry::SaveEngineDefaults()
	{
		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		{ // DATA

		}

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / "engine");
		ofs << buffer.GetString();
		ofs.close();
	}

	void SettingsRegistry::SaveEditorDefaults()
	{
		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		{ // DATA

		}

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / "editor");
		ofs << buffer.GetString();
		ofs.close();
	}

	void SettingsRegistry::SaveUserDefaults()
	{
		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		{ // DATA

		}

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / "user");
		ofs << buffer.GetString();
		ofs.close();
	}

	void SettingsRegistry::SaveBuildDefaults()
	{
		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		{ // DATA

		}

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / "build");
		ofs << buffer.GetString();
		ofs.close();
	}

	void SettingsRegistry::SaveNetworkDefaults()
	{
		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		{ // DATA

		}

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / "network");
		ofs << buffer.GetString();
		ofs.close();
	}

	void SettingsRegistry::SavePhysicsDefaults()
	{
		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		{ // DATA

		}

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / "physics");
		ofs << buffer.GetString();
		ofs.close();
	}

#pragma endregion

	void SettingsRegistry::Save()
	{
		SaveLayer("build");
		SaveLayer("graphics");
		SaveLayer("user");
		SaveLayer("engine");
		SaveLayer("editor");
		SaveLayer("network");
		SaveLayer("physics");
	}

	void SettingsRegistry::SaveLayer(const char* layerName)
	{
		using namespace rapidjson;

		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		for (auto& [settingKey, data] : layers[layerName].values)
		{
			d.AddMember(Value(settingKey.c_str(), allocator).Move(), VariantToJson(data, allocator).Move(), allocator);
		}

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(PathManager::GetConfigDir() / layerName);
		ofs << buffer.GetString();
		ofs.close();
	}

#pragma endregion


#pragma region ---- LOADING

	void SettingsRegistry::Load()
	{
		Clear();

		if (!std::filesystem::exists(PathManager::GetConfigDir() / "graphics")) SaveGraphicsDefaults();
		LoadLayer("graphics");

		if (!std::filesystem::exists(PathManager::GetConfigDir() / "user"))	SaveUserDefaults();
		LoadLayer("user");

		if (!std::filesystem::exists(PathManager::GetConfigDir() / "engine")) SaveEngineDefaults();
		LoadLayer("engine");

		if (!std::filesystem::exists(PathManager::GetConfigDir() / "editor")) SaveEditorDefaults();
		LoadLayer("editor");

		if (!std::filesystem::exists(PathManager::GetConfigDir() / "build")) SaveBuildDefaults();
		LoadLayer("build");

		if (!std::filesystem::exists(PathManager::GetConfigDir() / "network")) SaveNetworkDefaults();
		LoadLayer("network");

		if (!std::filesystem::exists(PathManager::GetConfigDir() / "physics")) SavePhysicsDefaults();
		LoadLayer("physics");
	}

	SettingValue& SettingsRegistry::Set(const char* settingKey)
	{
		std::string key = settingKey;
		size_t dotPos = key.find_first_of('.');
		if (dotPos == std::string::npos) throw std::runtime_error("SettingsRegistry::Get<T> wrong type");

		std::string layerName = key.substr(0, dotPos);
		std::string settingsName = key.substr(dotPos + 1);

		SettingsLayer& layer = layers[layerName];
		SettingValue& storedVal = layer.values[settingsName];

		return storedVal;
	}

	void SettingsRegistry::Clear()
	{
		layers.clear();
	}

	void SettingsRegistry::LoadLayer(const char* layerName)
	{
		using namespace rapidjson;

		std::ifstream ifs(PathManager::GetConfigDir() / layerName);
		if (!ifs.is_open()) {
			SaveDefaults(layerName);
			return;
		}

		std::string jsonString((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());

		ifs.close();

		Document d;
		d.Parse(jsonString.c_str());

		SettingsLayer& layer = layers[layerName];
		for (auto it = d.MemberBegin(); it != d.MemberEnd();)
		{
			std::string name = it->name.GetString();

			layer.values[name] = JsonToVariant(it->value);

			it++;
		}
	}

#pragma endregion






	void SettingsRegistry::PushOverride(const char* settingsKey, SettingValue value)
	{
		SettingValue& storedValue = GetValue(settingsKey);
		storedValue = value;
	}

	SettingValue& SettingsRegistry::GetValue(const char* settingsKey)
	{
		std::string key = settingsKey;
		size_t dotPos = key.find_first_of('.');
		if (dotPos == std::string::npos) throw std::runtime_error("SettingsRegistry::Get<T> wrong type");

		std::string layerKey = key.substr(0, dotPos);

		auto it = layers.find(layerKey);
		if (it != layers.end())
		{
			SettingsLayer& layer = it->second;
			std::string settingKey = key.substr(dotPos + 1);

			auto it = layer.values.find(settingKey);
			if (it != layer.values.end())
			{
				return it->second;
			}
			else
			{
				return AddValue(layer, settingKey.c_str());
			}
		}

		throw std::runtime_error("SettingsRegistry::Get<T> wrong type");
	}

	SettingValue& SettingsRegistry::AddValue(SettingsLayer& layer, const char* key)
	{
		std::string settingKey = key;
		layer.values[settingKey] = {};

		return layer.values[settingKey];
	}

	rapidjson::Value SettingsRegistry::VariantToJson(const SettingValue& value, rapidjson::Document::AllocatorType& allocator)
	{
		if (std::holds_alternative<bool>(value))
			return rapidjson::Value(std::get<bool>(value));
		if (std::holds_alternative<int>(value))
			return rapidjson::Value(std::get<int>(value));
		if (std::holds_alternative<float>(value))
			return rapidjson::Value(std::get<float>(value));
		if (std::holds_alternative<double>(value))
			return rapidjson::Value(std::get<double>(value));
		if (std::holds_alternative<std::string>(value))
			return rapidjson::Value(std::get<std::string>(value).c_str(), allocator);

		if (std::holds_alternative<Math::Vector2i>(value))
		{
			rapidjson::Value obj(rapidjson::kObjectType);
			auto v = std::get<Math::Vector2i>(value);
			obj.AddMember("x", v.x, allocator);
			obj.AddMember("y", v.y, allocator);
			return obj;
		}

		if (std::holds_alternative<Math::Vector2f>(value))
		{
			rapidjson::Value obj(rapidjson::kObjectType);
			auto v = std::get<Math::Vector2f>(value);
			obj.AddMember("x", v.x, allocator);
			obj.AddMember("y", v.y, allocator);
			return obj;
		}

		throw std::runtime_error("Unsupported SettingValue type");
	}

	SettingValue SettingsRegistry::JsonToVariant(const rapidjson::Value& jsonValue)
	{
		if (jsonValue.IsBool())   return jsonValue.GetBool();
		if (jsonValue.IsInt())    return jsonValue.GetInt();
		if (jsonValue.IsFloat())  return jsonValue.GetFloat();
		if (jsonValue.IsDouble()) return jsonValue.GetDouble();
		if (jsonValue.IsString()) return std::string(jsonValue.GetString());

		if (jsonValue.IsObject())
		{
			if (jsonValue.HasMember("x") && jsonValue.HasMember("y"))
			{
				if (jsonValue["x"].IsInt() && jsonValue["y"].IsInt())
				{
					return Math::Vector2i{
						jsonValue["x"].GetInt(),
						jsonValue["y"].GetInt()
					};
				}

				if (jsonValue["x"].IsNumber() && jsonValue["y"].IsNumber())
				{
					return Math::Vector2f{
						jsonValue["x"].GetFloat(),
						jsonValue["y"].GetFloat()
					};
				}
			}
		}

		throw std::runtime_error("Unsupported JSON value");
	}
}