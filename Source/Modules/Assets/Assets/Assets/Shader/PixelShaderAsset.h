#pragma once

#include "ShaderAsset.h"
#include "Assets.Core.hpp"


namespace Eclipse::Assets
{
	struct ASSET_API PixelShader : public Shader
	{
		ASSET_IMPL(PixelShader, ShaderData)

	public:
		unsigned GetProgramID() const;

		void Bind();
	};
}