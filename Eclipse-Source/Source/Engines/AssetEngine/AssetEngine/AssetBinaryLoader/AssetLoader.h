#pragma once

#include "AssetEngine/Models/ImportedAssets.h"
#include "AssetEngine/Models/AssetDatas/Handles/AssetHandle.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Texture/TextureLoader.h"

namespace Eclipse::Assets
{
	class AssetLoader
	{
	public:
		static AssetHandle* Load(const size_t& id);

	private:
		static inline TextureLoader textureLoader{};
	};
}