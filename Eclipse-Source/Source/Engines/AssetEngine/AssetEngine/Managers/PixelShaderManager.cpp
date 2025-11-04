#include "AssetEngine/Managers/PixelShaderManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/PixelShader/PixelShaderLoader.h"
#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	PixelShaders PixelShaderManager::GetDefault()
	{
		static size_t id = AssetRegistry::GetInstance().GetIdFromPath("EngineAssets/Default/Shaders/DefaultSprite.pglsl");
		return Get(id);
	}

	PixelShaders PixelShaderManager::Get(const size_t& id)
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

	PixelShaders PixelShaderManager::Load(const size_t& id)
	{
		idToAssetHandle[id] = GetLoader().Load(id);
		return ConstructAsset(id);
	}

	PixelShaders PixelShaderManager::ConstructAsset(const size_t& id)
	{
		PixelShaders texture(idToAssetHandle[id]);

		return texture;
	}
}