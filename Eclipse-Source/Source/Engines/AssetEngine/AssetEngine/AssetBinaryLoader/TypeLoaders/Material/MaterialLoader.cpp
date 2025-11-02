#include "MaterialLoader.h"

#include <filesystem>
#include "AssetEngine/AssetImporter/TypeImporters/Texture/STB_ImporterStrategy.h"

#include "AssetEngine/AssetCooker/CookedAsset.h"
#include "AssetEngine/AssetRegistry.h"
#include "AssetEngine/PathManager.h"

#include "AssetEngine/Resources.h"

namespace Eclipse::Assets
{
	MaterialHandle* Eclipse::Assets::MaterialLoader::Load(const size_t& id)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);

		std::ifstream in(entry.path, std::ios::binary);

		MaterialHandle* handle = new MaterialHandle;
		handle->assetID = id;

		size_t textureID = 0, psID = 0, vsID = 0;

		Math::Color color = { 1.f ,1.f, 1.f, 1.f };
		in.read(reinterpret_cast<char*>(&textureID), sizeof(size_t)); // Texture id
		in.read(reinterpret_cast<char*>(&psID), sizeof(size_t)); // ps
		in.read(reinterpret_cast<char*>(&vsID), sizeof(size_t)); // vs
		in.read(reinterpret_cast<char*>(&color), sizeof(Math::Color)); // color
		in.close();

		handle->texture = Resourcess::Get<Textures>(textureID);
		handle->ps = Resourcess::Get<PixelShaders>(psID);
		handle->vs = Resourcess::Get<VertexShaders>(vsID);

		return handle;
	}
}