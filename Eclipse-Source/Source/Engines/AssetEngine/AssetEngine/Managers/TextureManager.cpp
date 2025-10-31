#include "AssetEngine/Managers/TextureManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Texture/TextureLoader.h"

#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	Textures TextureManager::GetDefault()
	{
		static size_t id = AssetRegistry::GetInstance().GetIdFromPath("EngineAssets/Default/Textures/Default_Texture.png");
		return Get(id);
	}

	Textures TextureManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	Textures TextureManager::Load(const size_t& id)
	{
		static Assets::TextureLoader textureLoader{};

		idToAssetHandle[id] = textureLoader.Load(id);
		return ConstructAsset(id);
	}

	Textures TextureManager::ConstructAsset(const size_t& id)
	{
		Textures texture(idToAssetHandle[id]);

		return texture;
	}
}