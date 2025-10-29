#include "AssetEngine/Managers/PixelShaderManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/PixelShader/PixelShaderLoader.h"

namespace Eclipse::Assets
{
	Shaders PixelShaderManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	Shaders PixelShaderManager::Load(const size_t& id)
	{
		static Assets::PixelShaderLoader loader{};

		idToAssetHandle[id] = loader.Load(id);
		return ConstructAsset(id);
	}

	Shaders PixelShaderManager::ConstructAsset(const size_t& id)
	{
		Shaders texture(idToAssetHandle[id]);

		return texture;
	}
}