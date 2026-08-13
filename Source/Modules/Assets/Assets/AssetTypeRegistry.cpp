#include "AssetTypeRegistry.h"

#include "AssetTypes/AudioAssetType.h"
#include "AssetTypes/FontAssetType.h"
#include "AssetTypes/MaterialAssetType.h"
#include "AssetTypes/PrefabAssetType.h"
#include "AssetTypes/VertexShaderAssetType.h"
#include "AssetTypes/PixelShaderAssetType.h"
#include "AssetTypes/TextureAssetType.h"
#include "AssetTypes/SceneAssetType.h"

namespace Eclipse::Assets
{
	void AssetTypeRegistry::RegisterTypes()
	{
		types[AssetType::AudioClip] = new AudioAssetType;
		types[AssetType::Font] = new FontAssetType;
		types[AssetType::Material] = new MaterialAssetType;
		types[AssetType::Prefab] = new PrefabAssetType;
		types[AssetType::VertexShader] = new VertexShaderAssetType;
		types[AssetType::PixelShader] = new PixelShaderAssetType;
		types[AssetType::Texture] = new TextureAssetType;
		types[AssetType::Scene] = new SceneAssetType;
	}

	IAssetType* AssetTypeRegistry::GetType(AssetType assetType)
	{
		auto it = types.find(assetType);
		if (it == types.end()) return nullptr;

		return it->second;
	}
}