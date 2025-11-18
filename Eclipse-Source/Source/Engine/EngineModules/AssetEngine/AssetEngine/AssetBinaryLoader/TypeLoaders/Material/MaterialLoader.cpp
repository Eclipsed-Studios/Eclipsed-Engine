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


		MaterialHandle* handle = new MaterialHandle;

		Load(id, handle);
		return handle;
	}

	void MaterialLoader::Load(const size_t& id, MaterialHandle* handle)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);

		std::ifstream in(entry.path, std::ios::binary);
		handle->assetID = id;

		size_t textureID = 0, psID = 0, vsID = 0;

		Math::Color color = { 1.f ,1.f, 1.f, 1.f };
		in.read(reinterpret_cast<char*>(&textureID), sizeof(size_t)); // Texture id
		in.read(reinterpret_cast<char*>(&psID), sizeof(size_t)); // ps
		in.read(reinterpret_cast<char*>(&vsID), sizeof(size_t)); // vs
		in.read(reinterpret_cast<char*>(&color), sizeof(Math::Color)); // color
		in.close();

		handle->texture = Resources::Get<Texture>(textureID);
		handle->ps = Resources::Get<PixelShader>(psID);
		handle->vs = Resources::Get<VertexShader>(vsID);
	}
}