#include "AssetLoader.h"

#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	AssetHandle* AssetLoader::Load(const size_t& id)
	{
		AssetRegistry& registry = AssetRegistry::GetInstance();
	
		if (!registry.IsRegistered(id)) return nullptr;

		const AssetRegistryEntry& entry = registry.GetRegisteredAsset(id);

		switch ((AssetType)entry.type)
		{
		case AssetType::Texture: return textureLoader.Load(id);
		case AssetType::Material: return materialLoader.Load(id);
		case AssetType::PixelShader: return pixelShaderLoader.Load(id);
		case AssetType::VertexShader: return vertexShaderLoader.Load(id);
		}

		return nullptr;
	}
}