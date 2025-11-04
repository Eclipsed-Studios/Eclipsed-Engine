#include "AssetEngine/Managers/VertexShaderManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/VertexShader/VertexShaderLoader.h"
#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	VertexShaders VertexShaderManager::GetDefault()
	{
		static size_t id = AssetRegistry::GetInstance().GetIdFromPath("EngineAssets/Default/Shaders/DefaultSprite.vglsl");
		return Get(id);
	}

	VertexShaders VertexShaderManager::Get(const size_t& id)
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

	VertexShaders VertexShaderManager::Load(const size_t& id)
	{
		idToAssetHandle[id] = GetLoader().Load(id);
		return ConstructAsset(id);
	}

	VertexShaders VertexShaderManager::ConstructAsset(const size_t& id)
	{
		VertexShaders texture(idToAssetHandle[id]);

		return texture;
	}
}