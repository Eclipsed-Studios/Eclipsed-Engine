#include "AssetEngine/Managers/TextureManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Texture/TextureLoader.h"

namespace Eclipse::Assets
{
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