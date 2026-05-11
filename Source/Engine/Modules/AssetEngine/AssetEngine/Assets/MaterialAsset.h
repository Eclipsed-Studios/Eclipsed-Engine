#pragma once

#include "AssetEngine/Assets/Asset.h"

#include "AssetEngine/BinaryFormats/MaterialData.h"
#include "CoreEngine/GraphicsBuffers/MaterialBuffer.h"


namespace Eclipse::Assets
{
	struct Material : public Asset<MaterialData> {
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