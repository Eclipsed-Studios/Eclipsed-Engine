#include "AssetFactory.h"

#include <fstream>

#include "AssetEngine/Models/AssetDatas/Handles/MaterialHandle.h"
#include "AssetEngine/Resources.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Texture/TextureLoader.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/VertexShader/VertexShaderLoader.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/PixelShader/PixelShaderLoader.h"

#include "CoreEngine/PathManager.h"

namespace Eclipse::Assets
{


	void AssetFactory::CreateMaterial(const char* path)
	{
		//std::ofstream out(path, std::ios::binary);

		Texture texture = Resources::GetDefaultTexture();
		VertexShader vs = Resources::GetDefaultVS();
		PixelShader ps = Resources::GetDefaultPS();

		MaterialData data;
		data.Texture = texture.GetAssetID();
		data.VertexShader = vs.GetAssetID();
		data.PixelShader = ps.GetAssetID();

		std::ofstream out(path);
		cereal::JSONOutputArchive archive(out);
		archive(data);
	}
}