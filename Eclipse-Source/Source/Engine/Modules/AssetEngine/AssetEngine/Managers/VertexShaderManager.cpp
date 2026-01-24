#include "AssetEngine/Managers/VertexShaderManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/VertexShader/VertexShaderLoader.h"
#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	VertexShader VertexShaderManager::GetDefault()
	{
		static size_t id = AssetRegistry::GetInstance().GetIdFromPath("Assets/EngineAssets/Default/Shaders/DefaultSprite.vglsl");
		return Get(id);
	}

	VertexShader VertexShaderManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	VertexShaderLoader& VertexShaderManager::GetLoader()
	{
		static Assets::VertexShaderLoader loader{};
		return loader;
	}


	void VertexShaderManager::Reload(const size_t& id)
	{
		Assets::ShaderHandle* handle = idToAssetHandle[id];

		int refcount = handle->refCount;
		handle = GetLoader().Load(id);

		handle->refCount = refcount;
	}

	VertexShader VertexShaderManager::Load(const size_t& id)
	{
		idToAssetHandle[id] = GetLoader().Load(id);
		return ConstructAsset(id);
	}

	VertexShader VertexShaderManager::ConstructAsset(const size_t& id)
	{
		VertexShader texture(idToAssetHandle[id]);

		return texture;
	}
}