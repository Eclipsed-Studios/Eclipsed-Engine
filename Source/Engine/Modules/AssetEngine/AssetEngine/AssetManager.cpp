#include "AssetManager.h"

#include "CoreEngine/MainSingleton.h"
#include "AssetEngine/Core/EditorAssetDatabase.h"

#include "AssetTypes/IAssetType.h"
#include "IO/BinaryWriter.h"

#include "AssetTypeRegistry.h"

namespace Eclipse::Assets
{
	void AssetManager::ImportAssets(const std::filesystem::path& root, const std::string& key)
	{
		if (!MainSingleton::Exists<AssetDatabase>())
		{
			MainSingleton::RegisterInstance<AssetDatabase>();
			AssetTypeRegistry::RegisterTypes();
		}

		AssetDatabase& database = MainSingleton::GetInstance<AssetDatabase>();
		database.ProcessSource(root, key);

		for (auto& [guid, file] : database.GetSources())
		{
			if (!FileWasChanged(file)) 
				continue;

			ImportFile(file);
		}
	}



	void AssetManager::EndFrame()
	{
		// delete makred for delete assets.
	}

	void AssetManager::ImportFile(const AssetMeta& meta)
	{
		AssetType assetType = GetAssetTypeFromExtension(meta.fullPath.extension().string());
		IAssetType* type = AssetTypeRegistry::GetType(assetType);

		ImportedData imported = type->Import(meta);
		BinaryWriter writer(meta.guid);

		if (type->NeedsProcessing())
		{
			ProcessedData processed = type->Process(imported);
			type->Serialize(writer, processed);
		}
		else
		{
			type->Serialize(writer, imported);
		}
	}

	bool AssetManager::FileWasChanged(const AssetMeta& meta)
	{
		std::filesystem::path exportedPath = PathManager::GetArtifactsPath();
		std::string guidStr = meta.guid.ToString();

		exportedPath /= guidStr.substr(0, 2);
		exportedPath /= guidStr;

		if (!std::filesystem::exists(exportedPath))
			return true;

		std::filesystem::path metaPath = meta.fullPath;
		metaPath += ".meta";

		auto sourceTime = std::filesystem::last_write_time(meta.fullPath);
		auto exportTime = std::filesystem::last_write_time(exportedPath);

		bool sourceChanged = sourceTime > exportTime;

		bool metaChanged = false;
		if (std::filesystem::exists(metaPath))
		{
			auto metaTime = std::filesystem::last_write_time(metaPath);
			metaChanged = metaTime > exportTime;
		}

		return sourceChanged || metaChanged;
	}
}