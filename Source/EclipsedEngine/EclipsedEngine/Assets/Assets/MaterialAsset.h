#pragma once

#include "EclipsedEngine/Assets/Asset.h"

#include "EclipsedEngine/Assets/BinaryFormats/MaterialData.h"
#include "EclipsedEngine/Graphics/Buffers/MaterialBuffer.h"
#include "EclipsedEngine.Core.hpp"


namespace Eclipse::Assets
{
	struct ECL_API Material : public Asset<MaterialData> {
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