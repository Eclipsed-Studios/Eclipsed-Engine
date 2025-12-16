#pragma once

#include <unordered_map>
#include <string>
#include "AssetEngine/Models/AssetType.h"

namespace Eclipse::Assets
{
	inline std::unordered_map<std::string, AssetType> extensionToAssetType =
	{
		{".png",  AssetType::Texture},
		{".jpg",  AssetType::Texture},
		{".jpeg", AssetType::Texture},
		{".bmp",  AssetType::Texture},
		{".tga",  AssetType::Texture},
		{".psd",  AssetType::Texture},
		{".gif",  AssetType::Texture},
		{".hdr",  AssetType::Texture},
		{".pic",  AssetType::Texture},
		{".pnm",  AssetType::Texture},

		{".mat",  AssetType::Material},

		{".vglsl",  AssetType::VertexShader},

		{".pglsl",  AssetType::PixelShader},

		{".mp3",  AssetType::AudioClip},
	};
}