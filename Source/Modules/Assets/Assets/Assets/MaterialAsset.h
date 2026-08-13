#pragma once

#include "Assets/Assets/Asset.h"

#include "Assets/BinaryFormats/MaterialData.h"
#include "Core/GraphicsBuffers/MaterialBuffer.h"
#include "Assets.Core.hpp"


namespace Eclipse::Assets
{
	struct ASSET_API Material : public Asset<MaterialData> {
		ASSET_IMPL(Material, MaterialData)

	public:

		Texture GetTexture() const;
		PixelShader GetPixelShader() const;
		VertexShader GetVertexShader() const;

	public:
		void BindTexture();
		void BindShader();
		void BindColor();

		void Use();
		void Create();

		MaterialBuffer materialBuffer;
	};
}