#include "AssetFactory.h"

#include <fstream>

#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"
#include "AssetEngine/Resources.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Texture/TextureLoader.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/VertexShader/VertexShaderLoader.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/PixelShader/PixelShaderLoader.h"

namespace Eclipse::Assets
{
	void AssetFactory::CreateMaterial(const char* path)
	{
		std::ofstream out(path, std::ios::binary);

		Textures texture = Resourcess::GetDefaultTexture();
		VertexShaders vs = Resourcess::GetDefaultVS();
		PixelShaders ps = Resourcess::GetDefaultPS();

		size_t textureID = texture.GetAssetID();
		size_t vsID = vs.GetAssetID();
		size_t psID = ps.GetAssetID();

		Math::Color color = { 1.f ,1.f, 1.f, 1.f };
		out.write(reinterpret_cast<const char*>(&textureID), sizeof(size_t)); // Texture id
		out.write(reinterpret_cast<const char*>(&psID), sizeof(size_t)); // ps
		out.write(reinterpret_cast<const char*>(&vsID), sizeof(size_t)); // vs
		out.write(reinterpret_cast<const char*>(&color), sizeof(Math::Color)); // color
		out.close();
	}
}