#include "AssetEngine/Managers/PixelShaderManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/PixelShader/PixelShaderLoader.h"
#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	PixelShader PixelShaderManager::GetDefault()
	{
		static size_t id = AssetRegistry::GetInstance().GetIdFromPath("Assets/EngineAssets/Default/Shaders/DefaultSprite.pglsl");
		return Get(id);
	}

	PixelShader PixelShaderManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	PixelShaderLoader& PixelShaderManager::GetLoader()
	{
		static Assets::PixelShaderLoader loader{};
		return loader;
	}

	void PixelShaderManager::Reload(const size_t& id)
	{
		Assets::ShaderHandle* handle = idToAssetHandle[id];

		int refcount = handle->refCount;
		handle = GetLoader().Load(id);

		handle->refCount = refcount;
	}

	PixelShader PixelShaderManager::Load(const size_t& id)
	{
		idToAssetHandle[id] = GetLoader().Load(id);
		return ConstructAsset(id);
	}

	PixelShader PixelShaderManager::ConstructAsset(const size_t& id)
	{
		PixelShader texture(idToAssetHandle[id]);

		return texture;
	}
}