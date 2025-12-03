#pragma once

#include "AssetEngine/Models/ImportedAssets.h"
#include "AssetEngine/Models/AssetDatas/Handles/AssetHandle.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Texture/TextureLoader.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Material/MaterialLoader.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/PixelShader/PixelShaderLoader.h"
#include "AssetEngine/AssetBinaryLoader/TypeLoaders/VertexShader/VertexShaderLoader.h"

namespace Eclipse::Assets
{
	class AssetLoader
	{
	public:
		static AssetHandle* Load(const size_t& id);

	private:
		static inline TextureLoader textureLoader{};
		static inline MaterialLoader materialLoader{};
		static inline PixelShaderLoader pixelShaderLoader{};
		static inline VertexShaderLoader vertexShaderLoader{};
	};
}