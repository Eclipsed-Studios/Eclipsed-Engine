#include "AssetManager.h"

#include "CoreEngine/MainSingleton.h"
#include "AssetEngine/Core/EditorAssetDatabase.h"

#include "AssetTypes/AudioAssetType.h"
#include "AssetTypes/FontAssetType.h"
#include "AssetTypes/MaterialAssetType.h"
#include "AssetTypes/PrefabAssetType.h"
#include "AssetTypes/ShaderAssetType.h"
#include "AssetTypes/TextureAssetType.h"
#include "IO/BinaryWriter.h"

namespace Eclipse::Assets
{
	Font AssetManager::GetDefaultFont()
	{
		return Font();
	}

	Material AssetManager::GetDefaultUIMaterial()
	{
		return Material();
	}

	void AssetManager::ImportAssets(const std::filesystem::path& path, const std::string& key)
	{
		if (!MainSingleton::Exists<AssetDatabase>())
		{
			MainSingleton::RegisterInstance<AssetDatabase>();
			RegisterTypes();
		}

		AssetDatabase& database = MainSingleton::GetInstance<AssetDatabase>();
		database.ProcessSource(path, key);

		for (auto& [guid, file] : database.GetSources())
		{
			AssetType assetType = GetAssetTypeFromExtension(file.fullPath.extension().string());
			IAssetType* type = GetType(assetType);

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

	void AssetManager::RegisterTypes()
	{
		types[AssetType::AudioClip] = new AudioAssetType;
		types[AssetType::Font] = new FontAssetType;
		types[AssetType::Material] = new MaterialAssetType;
		types[AssetType::Prefab] = new PrefabAssetType;
		types[AssetType::VertexShader] = new ShaderAssetType;
		types[AssetType::PixelShader] = new ShaderAssetType;
		types[AssetType::Texture] = new TextureAssetType;
	}

	IAssetType* AssetManager::GetType(AssetType assetType)
	{
		auto it = types.find(assetType);
		if (it == types.end()) return nullptr;

		return it->second;
	}
}