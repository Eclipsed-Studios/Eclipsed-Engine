#pragma once

#include "EclipsedEngine/Assets/BinaryFormats/ShaderData.h"
#include "EclipsedEngine/Assets/Asset.h"
#include "ShaderAsset.h"
#include "EclipsedEngine.Core.hpp"


namespace Eclipse::Assets
{
	struct ECL_API PixelShader : public Shader
	{
		ASSET_IMPL(PixelShader, ShaderData)

	public:
		unsigned GetProgramID() const;
	};
}