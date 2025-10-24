#include "AssetRegistry.h"

#include "PathManager.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/prettywriter.h"

namespace Eclipse::Assets
{
	AssetRegistry& AssetRegistry::GetInstance()
	{
		static AssetRegistry instance{};

		if(metafilePath.empty()) metafilePath = PathManager::GetCookedAssetsDir() / "assets.data";

		return instance;
	}

	void AssetRegistry::Load()
	{
		using namespace rapidjson;

		if (!std::filesystem::exists(metafilePath)) return;

		FILE* fileP = fopen(metafilePath.string().c_str(), "rb");
		char readBuffer[2048];
		FileReadStream fileReadStream(fileP, readBuffer, sizeof(readBuffer));

		Document d;
		d.ParseStream(fileReadStream);
		fclose(fileP);

		Value& list = d["assets"];

		for (auto& asset : list.GetArray())
		{
			AssetRegistryEntry entry;
			size_t id = asset["id"].GetUint64();
			entry.lastModified = asset["lastmodifed"].GetUint64();
			entry.path = asset["path"].GetString();
			entry.type = asset["type"].GetInt();

			registeredAssets[id] = entry;
		}
	}

	void AssetRegistry::Save()
	{
		using namespace rapidjson;

		Document d;
		d.SetObject();
		Document::AllocatorType& allocator = d.GetAllocator();

		Value list(kArrayType);

		for (auto& [id, data] : registeredAssets)
		{
			Value val(kObjectType);

			std::string idString = std::to_string(id);
			val.AddMember("id", id, allocator);

			val.AddMember("path", Value(data.path.string().c_str(), allocator).Move(), allocator);
			val.AddMember("lastmodifed", data.lastModified, allocator);
			val.AddMember("type", data.type, allocator);

			list.PushBack(val, allocator);
		}

		d.AddMember("assets", list, allocator);

		StringBuffer buffer;
		PrettyWriter<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(metafilePath);
		ofs << buffer.GetString();
		ofs.close();
	}

	void AssetRegistry::RegisterAsset(const std::filesystem::path& fullPath, const std::filesystem::path& relativePath, AssetType type)
	{
		if (std::filesystem::is_directory(fullPath)) return;

		size_t id = GetIdFromPath(relativePath);

		AssetRegistryEntry entry;

		size_t lastModTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::filesystem::last_write_time(fullPath).time_since_epoch()).count();
		entry.lastModified = lastModTime;
		entry.path = fullPath;
		entry.type = (int)type;

		registeredAssets[id] = entry;
	}

	void AssetRegistry::UnregisterAsset(const size_t& id)
	{
		registeredAssets.erase(id);
	}

	const AssetRegistryEntry& AssetRegistry::GetRegisteredAsset(const size_t& id)
	{
		if (registeredAssets.find(id) == registeredAssets.end()) 
			return {};

		return registeredAssets[id];
	}
	
	const AssetRegistryEntry& AssetRegistry::GetRegisteredAsset(const std::filesystem::path& relativePath)
	{
		return GetRegisteredAsset(GetIdFromPath(relativePath));
	}

	const std::unordered_map<size_t, AssetRegistryEntry>& AssetRegistry::GetRegisteredAssets()
	{
		return registeredAssets;
	}

	bool AssetRegistry::IsRegistered(const size_t& id)
	{
		return registeredAssets.find(id) != registeredAssets.end();
	}

	bool AssetRegistry::IsRegistered(const std::filesystem::path& relativePath)
	{
		return IsRegistered(GetIdFromPath(relativePath));
	}
	
	size_t AssetRegistry::GetIdFromPath(const std::filesystem::path& relativePath)
	{
		return std::hash<std::string>{}(relativePath.generic_string());
	}
}