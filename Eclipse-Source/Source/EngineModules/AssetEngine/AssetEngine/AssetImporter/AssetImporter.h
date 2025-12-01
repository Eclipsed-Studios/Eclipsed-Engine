#pragma once

#include "TypeImporters/Texture/TextureImporter.h"
#include "AssetEngine/Models/ImportedAssets.h"

#include "AssetEngine/Models/AssetType.h"

namespace Eclipse::Assets
{
	class AssetImporter
	{
	public:
		static void Import(const char* path, const char* rel, ImportedAsset& outAsset);

	private:
		static inline TextureImporter textureImporter{};
	};
}

#include "AssetImporter.inl"