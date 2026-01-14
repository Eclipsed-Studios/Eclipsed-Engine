#include "AssetEngine/Managers/AnimationManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Animation/SpriteAnimationLoader.h"

#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	// Texture TextureManager::GetDefault()
	// {
	// 	static size_t id = AssetRegistry::GetInstance().GetIdFromPath("EngineAssets/Default/Textures/Default_Texture.png");
	// 	return Get(id);
	// }

	// Texture TextureManager::Get(const size_t& id)
	// {
	// 	if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
	// 	else return Load(id);
	// }

	// TextureLoader& TextureManager::GetLoader()
	// {
	// 	static Assets::TextureLoader textureLoader{};
	// 	return textureLoader;
	// }

	// void TextureManager::Reload(const size_t& id)
	// {
	// 	Assets::TextureHandle* handle = idToAssetHandle[id];

	// 	int refcount = handle->refCount;
	// 	handle = GetLoader().Load(id);

	// 	handle->refCount = refcount;
	// }

	// Texture TextureManager::Load(const size_t& id)
	// {
	// 	idToAssetHandle[id] = GetLoader().Load(id);
	// 	return ConstructAsset(id);
	// }

	// Texture TextureManager::ConstructAsset(const size_t& id)
	// {
	// 	Texture texture(idToAssetHandle[id]);

	// 	return texture;
	// }
}