#include "AssetManager.h"

#include "CoreEngine/MainSingleton.h"
#include "AssetEngine/Core/EditorAssetDatabase.h"

#include "AssetTypes/IAssetType.h"
#include "IO/BinaryWriter.h"

#include "AssetTypeRegistry.h"

namespace Eclipse::Assets
{
	void AssetManager::ImportAssets(const std::filesystem::path& path, const std::string& key)
	{
		if (!MainSingleton::Exists<AssetDatabase>())
		{
			MainSingleton::RegisterInstance<AssetDatabase>();
			AssetTypeRegistry::RegisterTypes();
		}

		AssetDatabase& database = MainSingleton::GetInstance<AssetDatabase>();
		database.ProcessSource(path, key);

		for (auto& [guid, file] : database.GetSources())
		{
			AssetType assetType = GetAssetTypeFromExtension(file.fullPath.extension().string());
			IAssetType* type = AssetTypeRegistry::GetType(assetType);

			ImportedData imported = type->Import(file);
			BinaryWriter writer(guid);

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
	}



	void AssetManager::EndFrame()
	{
		// delete makred for delete assets.
	}
}