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

	PixelShaders PixelShaderManager::Load(const size_t& id)
	{
		static Assets::PixelShaderLoader loader{};

		idToAssetHandle[id] = loader.Load(id);
		return ConstructAsset(id);
	}

	PixelShaders PixelShaderManager::ConstructAsset(const size_t& id)
	{
		PixelShaders texture(idToAssetHandle[id]);

		return texture;
	}
}