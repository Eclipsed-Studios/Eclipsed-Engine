#pragma once

#include "TypeImporters/Texture/TextureImporter.h"
#include "AssetEngine/Models/ImportedAssets.h"

#include "AssetEngine/Models/AssetType.h"

namespace Eclipse::Assets
{
	class AssetImporter
	{
	private:
		static inline std::unordered_map<std::string, AssetType> extensionToAssetType =
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
			{".pnm",  AssetType::Texture}
		};

	public:
		static void Import(const char* path, ImportedAsset& outAsset);

	private:
		static inline TextureImporter textureImporter{};
	};
}

#include "AssetImporter.inl"