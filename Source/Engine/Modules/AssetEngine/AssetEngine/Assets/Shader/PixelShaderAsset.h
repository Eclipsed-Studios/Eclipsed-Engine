#pragma once

#include "ShaderAsset.h"

namespace Eclipse::Assets
{
	struct PixelShader : public Shader
	{
		ASSET_IMPL(PixelShader, ShaderData)

	public:
		unsigned GetProgramID() const;

		void Bind();
	};
}